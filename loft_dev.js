/**
 * @file
 * The main javascript file for the loft_dev module
 *
 * @ingroup loft_dev
 * @{
 */

(function ($) {
  Drupal.loftDev = Drupal.loftDev || {};

  /**
   * A function to quickly clean up the view for layout checks.
   */
  Drupal.loftDev.hideAdminStuff = function() {
    // List of classes that are "admin stuff"--to hide.
    $(Drupal.settings.loftDev.adminStuff).hide();
    $("body.toolbar").css("padding-top", 0);
  };

  /**
   * Delete cookie and relad
   *
   * @return {[type]} [description]
   */
  Drupal.loftDev.showAdminStuff = function() {
    $(Drupal.settings.loftDev.adminStuff).show();
    $.cookie('loft_dev_admin_stuff', 'visible');
  };

  /**
  * Core behavior for loft_dev.
  */
  Drupal.behaviors.loftDev = Drupal.behaviors.loftDev || {};
  Drupal.behaviors.loftDev.attach = function (context, settings) {

    if ($.cookie('loft_dev_admin_stuff') === 'hidden') {
      Drupal.loftDev.hideAdminStuff();
      $('body')
      .once('loft_dev')
      .append('<a class="loft-dev-show-admin-stuff" onclick="Drupal.loftDev.showAdminStuff(); return false;">[+]</a>');
    }
    
    // Duration of the adminStuff cookie in mins
    var duration = 10;

    $('.loft-dev-hide-admin-trigger')
    .once('loft-dev')
    .click(function (e) {
      Drupal.loftDev.hideAdminStuff();

      // Was the meta key held down? Set cookie?
      if (e.metaKey) {
        console.log('metaKey');
        var expiry = new Date();
        var time = expiry.getTime();
        time += duration * 60 * 1000;
        expiry.setTime(time);        
        $.cookie('loft_dev_admin_stuff', "hidden", {"expires": expiry});
      };   

      return false;
    });

    if ($('#loft-dev-functions-list').length) {
      $('#loft-dev-functions-list').listSearchFilter($('#loft-dev-functions-filter'), {auto: 0});
    }

    if ($('#loft-dev-elements-list')) {
      $('#loft-dev-elements-list').listSearchFilter($('#loft-dev-elements-filter'), {auto: 0});
    }

    $('li .element-name a').click(function(){
      $(this).parents('li').find('.element-details').slideToggle();
      return false;
    });

  };

  /**
  * @} End of "defgroup loft_dev".
  */

})(jQuery);

/**
 * Create a searchable list by textfield jQuery Plugin
 *
 * @param object $input
 *   A jQuery object of a textfield to use as the search box
 * @param options
 *   code: the ascii code of the key to use for lookup; when this is pressed
     the list will be searched, defaults to 13 for the Return key.
 *   auto: min length needed before it will autosearch, for large lists
     setting this too low results in poor performance. Set this to 0 to turn off
     autosubmit.
 *
 * @return $(this)
 *
 * Attach this to a list and pass it an input to get a searchable list by the
   input field e.g.

   @code
    $('ul.list').listSearchFilter($('input.search'));
   @endcode
 *
 *
 * @author Aaron Klump, In the Loft Studios, LLC
 * @see http://www.intheloftstudios.com
 * @see http://gist.github.com/4278992
 */
(function($) {
  $.fn.listSearchFilter = function($input, options) {
    var $list = $(this);
    var settings = $.extend({
      'code'    : 13,
      'auto'    : 6
    }, options);

    /**
     * Filter the list with a needle
     */
    var filter = function(needle) {
      var $items = $list.find('li');
      $items
      .hide()
      .filter(function() {
        return $(this).text().indexOf(needle) !== -1;
      }).show();
    };

    /**
     * Handler of the input
     */
    $input.keypress(function(e) {
      var code = (e.keyCode ? e.keyCode : e.which);
      var needle = $(this).val();
      if((settings.auto && needle.length >= settings.auto) ||
         code === settings.code) {
        if (needle) {
          filter(needle);
        }
        else {
          $list.find('li:hidden').show();
        }
      }
    });
    return $(this);
  };
})(jQuery);
