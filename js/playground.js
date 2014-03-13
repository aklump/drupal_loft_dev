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
    Drupal.loftDev.hideAdminStuff();
  };
})(jQuery);