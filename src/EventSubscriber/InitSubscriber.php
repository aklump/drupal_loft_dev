<?php /**
 * @file
 * Contains \Drupal\loft_dev\EventSubscriber\InitSubscriber.
 */

namespace Drupal\loft_dev\EventSubscriber;

use Drupal\Core\StringTranslation\StringTranslationTrait;
use Drupal\Core\Url;
use Symfony\Component\EventDispatcher\EventSubscriberInterface;
use Symfony\Component\HttpKernel\Event\GetResponseForControllerResultEvent;
use Symfony\Component\HttpKernel\KernelEvents;
use Symfony\Component\Yaml\Yaml;

class InitSubscriber implements EventSubscriberInterface {

  use StringTranslationTrait;

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents() {
    return [
      KernelEvents::REQUEST => [
        ['onInit', 0],
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
        call_user_func_array($function, $sandbox['callback arguments']);
        exit(0);
      }
    }
  }

  public function onInit() {
    if (!_loft_dev_access()) {
      return;
    }

    $loft_dev = \Drupal::service('loft_dev');

    // Check our email configuration is correct.
    if (!$loft_dev->getProperlyConfiguredRerouteEmailAddress()) {
      drupal_set_message($this->t('Reroute email is not properly enabled/configured. You should add something like the following to <em>settings.local.php</em>.
<pre><code>
  $config[\'reroute_email.settings\'][\'enable\'] = TRUE;
  $config[\'reroute_email.settings\'][\'address\'] = \'aklump@imac-aaron.local\';
</code></pre>
', [
      ]), 'error', FALSE);
    }

    return;

    global $_loft_dev_playground, $_loft_dev_ignored_url;


    // Figure out some urls that need to be ignored, like image styles, etc.
    $_loft_dev_ignored_url = FALSE;
    if (strpos(Url::fromRoute("<current>")
        ->toString(), 'sites/default/files') === 0 || strpos(Url::fromRoute("<current>")
        ->toString(), 'system/ajax') === 0) {
      $_loft_dev_ignored_url = TRUE;
    }


    $_loft_dev_playground = _loft_dev_check_get_var('pg');


    $admin_stuff = module_invoke_all('loft_dev_admin_stuff');
    $build['#attached']['js'][] = [
      'type' => 'setting',
      'data' => [
        'loftDev' => [
          'adminStuff' => implode(', ', $admin_stuff['selectors']),
        ],
      ],
    ];
    $build['#attached']['library'][] = ['loft_dev', 'loft_dev'];
    \Drupal::service("renderer")->render($build);

    // Suppress admin menu if admin stuff hidden.
    if (isset($_COOKIE['loft_dev_admin_stuff']) && $_COOKIE['loft_dev_admin_stuff'] === 'hidden' && function_exists('admin_menu_suppress')) {
      admin_menu_suppress();
    }

  }

}
