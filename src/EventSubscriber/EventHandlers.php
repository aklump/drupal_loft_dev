<?php /**
 * @file
 * Contains \Drupal\loft_dev\EventSubscriber\InitSubscriber.
 */

namespace Drupal\loft_dev\EventSubscriber;

use Drupal\Core\Messenger\MessengerTrait;
use Drupal\Core\StringTranslation\StringTranslationTrait;
use Drupal\Core\Url;
use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Symfony\Component\HttpKernel\Event\GetResponseForControllerResultEvent;
use Symfony\Component\HttpKernel\KernelEvents;
use Symfony\Component\Yaml\Yaml;

class EventHandlers implements EventSubscriberInterface {

  use StringTranslationTrait;
  use MessengerTrait;

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents() {
    return [
      KernelEvents::REQUEST => [
        ['onInit', 0],
        ['onRequest', 0],
      ],
      KernelEvents::VIEW => [
        ['handleSandbox', 100],
      ],
    ];
  }

  public function handleSandbox(GetResponseForControllerResultEvent $event) {
    // TODO 'sb' is supposed to be configurable.
    // TODO This doesn't work to just pass 'sb', have to pass 'sb=1'; the former should work, so fix.
    $sandbox_is_enabled = $event->getRequest()->get('sb');
    if (!$sandbox_is_enabled) {
      return;
    }
    if (($theme = $event->getRequest()->get('theme'))) {
      \Drupal::theme()->setActiveTheme(\Drupal::service('theme.initialization')
        ->initTheme($theme));
    }

    global $_loft_dev_ignored_url;
    if ($_loft_dev_ignored_url) {
      return;
    }
    $sandboxes = \Drupal::moduleHandler()->invokeAll('loft_dev_sandbox');

    // Frontmatter to help developer know where he is.
    if ($sandboxes) {
      $frontmatter = [
        'activeTheme' => \Drupal::service('theme.manager')
          ->getActiveTheme()
          ->getName(),
      ];
      $header = [];
      $header[] = '---';
      $header[] = trim(Yaml::dump($frontmatter));
      $header[] = '---';
      print '<pre><code>' . implode(PHP_EOL, $header) . '</code></pre>';
    }

    foreach ($sandboxes as $sandbox) {
      if (_loft_dev_check_get_var($sandbox['query'])) {
        $function = $sandbox['callback'];
        call_user_func_array($function, $sandbox['callback arguments'] ?? []);
        exit(0);
      }
    }
  }

  public function onInit() {
    if (!_loft_dev_access()) {
      return;
    }

    // Do not worry about emails when running in Lando.
    if (!isset($_ENV["LANDO_HOST_IP"])) {
      $loft_dev = \Drupal::service('loft_dev');

      // Check our email configuration is correct.
      if (!$loft_dev->getProperlyConfiguredRerouteEmailAddress()) {
        $this->messenger()->addError($this->t('Reroute email is not properly enabled/configured. You should add something like the following to <em>settings.local.php</em>
<pre><code>
  $config[\'reroute_email.settings\'][\'enable\'] = TRUE;
  $config[\'reroute_email.settings\'][\'address\'] = \'aklump@imac-aaron.local\';
</code></pre>
To suppress this message you must disable Loft Dev module.', [
        ]), FALSE);
      }
    }
  }

  public function onRequest() {

    // Do an export if needed using loft_deploy shell script.
    if (_loft_dev_access() && ($period = \Drupal::config('loft_dev.settings')
        ->get('loft_deploy_export_period_mins'))) {
      $rollback = \Drupal::state()
        ->get('loft_dev.loft_deploy_export_last');
      $rollback += $period * 60;
      if (($now = time()) >= $rollback) {
        loft_dev_include('pages');

        // Important to set the state with an assumption it will not fail, so
        // that we don't have multiple backups running if it takes a long time.
        // If it fails, we'll delete the state below.
        \Drupal::state()->set('loft_dev.loft_deploy_export_last', $now);
        if (!loft_dev_loft_deploy_export('auto')) {
          \Drupal::state()->delete('loft_dev.loft_deploy_export_last');
          $message = 'Automatic database snapshot failed; please check loft_dev and/or loft_deploy.';
          \Drupal::messenger()->addError($message);
          \Drupal::logger('loft_dev')->error($message);
        }
      }
    }

    return;

    // Return the mail system to normal.
    global $_loft_dev_mail_system_stashed_, $_loft_dev_mail_filename_;
    if (!empty($_loft_dev_mail_system_stashed_)) {

      // Pop off our collected email.
      // @FIXME
      // // @FIXME
      // // This looks like another module's variable. You'll need to rewrite this call
      // // to ensure that it uses the correct configuration object.
      // $captured_emails = variable_get('drupal_test_email_collector');

      $message = array_pop($captured_emails);
      // @FIXME
      // // @FIXME
      // // This looks like another module's variable. You'll need to rewrite this call
      // // to ensure that it uses the correct configuration object.
      // variable_set('drupal_test_email_collector', $captured_emails);


      // Saves a copy of the message in the private files
      $url = $_loft_dev_mail_filename_ . '.exit.txt';
      file_unmanaged_save_data(var_export($message, TRUE), $url);
      // @FIXME
      // // @FIXME
      // // This looks like another module's variable. You'll need to rewrite this call
      // // to ensure that it uses the correct configuration object.
      // variable_set('mail_system', $_loft_dev_mail_system_stashed_);


      // Save a php version of this for export testing.
      if (($code = _loft_dev_compose_php_mail($message))) {
        $url = $_loft_dev_mail_filename_ . '.php';
        file_unmanaged_save_data($code, $url);
      }
    }

  }
}
