/**
 * @file
 * The main javascript file for the loft_dev module
 *
 * @ingroup loft_dev
 * @{
 */

(function ($) {
  Drupal.loftDev = Drupal.loftDev || {};
  Drupal.behaviors.loftDev = Drupal.behaviors.loftDev || {};
  Drupal.behaviors.loftDev.attach = function (context, settings) {
    console.log(Drupal.t('Playground has triggered Drupal.loftDev.hideAdminStuff.'));
    Drupal.loftDev.hideAdminStuff();
  };
})(jQuery);