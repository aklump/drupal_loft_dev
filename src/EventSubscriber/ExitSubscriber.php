<?php /**
 * @file
 * Contains \Drupal\loft_dev\EventSubscriber\ExitSubscriber.
 */

namespace Drupal\loft_dev\EventSubscriber;

use Symfony\Component\HttpKernel\KernelEvents;
use Symfony\Component\EventDispatcher\EventSubscriberInterface;

class ExitSubscriber implements EventSubscriberInterface {

  /**
   * {@inheritdoc}
   */
  public static function getSubscribedEvents() {
    return [KernelEvents::TERMINATE => ['onExit', 0]];
  }

  public function onExit() {
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

    // Do an export if needed using loft_deploy shell script.
    // @FIXME
    // Could not extract the default value because it is either indeterminate, or
    // not scalar. You'll need to provide a default value in
    // config/install/loft_dev.settings.yml and config/schema/loft_dev.schema.yml.
    if (_loft_dev_access() && ($period = \Drupal::config('loft_dev.settings')->get('loft_dev_loft_deploy_export_period_mins'))) {
      $now = new \DateTime('now', new \DateTimeZone('America/Los_Angeles'));
      $now = $now->format('U');
      $rollback = \Drupal::config('loft_dev.settings')->get('loft_dev_loft_deploy_export_last') + ($period * 60);
      if ($now >= $rollback) {
        loft_dev_include('pages');
        \Drupal::configFactory()->getEditable('loft_dev.settings')->set('loft_dev_loft_deploy_export_last', $now)->save();
        if (!loft_dev_loft_deploy_export('loft_dev_auto')) {
          \Drupal::configFactory()->getEditable('loft_dev.settings')->set('loft_dev_loft_deploy_export_last', $rollback)->save();
          if (_loft_dev_access()) {
            drupal_set_message(t("Loft Dev was unabled to export the database using <code>ld export</code>; review <a href='!uri'>reports</a> for more info.", [
              '!uri' => \Drupal\Core\Url::fromRoute('dblog.overview')
              ]), 'error');
          }
        }
      }
    }
  }

}
