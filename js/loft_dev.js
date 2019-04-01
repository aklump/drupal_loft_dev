/**
 * @file
 * The main javascript file for the loft_dev module
 *
 * @ingroup loft_dev
 * @{
 */

(function($) {
  Drupal.loftDev = Drupal.loftDev || {};

  /**
   * A function to quickly clean up the view for layout checks.
   */
  Drupal.loftDev.hideAdminStuff = function() {
    // List of classes that are "admin stuff"--to hide.
    $(drupalSettings.loftDev.adminStuff)
      .addClass('hidden-by-loft-dev')
      .hide();
    $('html').addClass('loft-dev--admin-is-hidden');
    $('body.toolbar').css('padding-top', 0);
  };

  /**
   * Delete cookie and reload
   *
   * @return {[type]} [description]
   */
  Drupal.loftDev.showAdminStuff = function() {
    $(drupalSettings.loftDev.adminStuff)
      .removeClass('hidden-by-loft-dev')
      .show();
    $.cookie('loft_dev_admin_stuff', 'visible');
  };

  /**
   * Core behavior for loft_dev.
   */
  Drupal.behaviors.loftDev = Drupal.behaviors.loftDev || {};
  Drupal.behaviors.loftDev.attach = function(context, settings) {
    if ($.cookie('loft_dev_admin_stuff') === 'hidden') {
      Drupal.loftDev.hideAdminStuff();
      $('body')
        .once('loft_dev')
        .append(
          '<a class="loft-dev-show-admin-stuff" onclick="Drupal.loftDev.showAdminStuff(); return false;">[+]</a>'
        );
    }

    // Duration of the adminStuff cookie in seconds
    var duration =
      typeof settings.loftDeploy !== 'undefined' &&
      typeof settings.loftDeploy.metaTimeout !== 'undefined'
        ? settings.loftDeploy.metaTimeout
        : 600;

    $('.loft-dev-hide-admin-trigger')
      .once('loft-dev')
      .click(function(e) {
        Drupal.loftDev.hideAdminStuff();

        // Was the meta key held down? Set cookie?
        if (e.metaKey) {
          override = prompt('Hide for how many minutes?', duration / 60);
          if (override) {
            var expiry = new Date(),
              time = expiry.getTime();
            if (override) {
              duration = override * 60;
            }
            time += duration * 1000;
            expiry.setTime(time);
            console.log(expiry);
            $.cookie('loft_dev_admin_stuff', 'hidden', { expires: expiry });
          }
        }

        return false;
      });

    if ($('#loft-dev-functions-list').length) {
      $('#loft-dev-functions-list').listSearchFilter(
        $('#loft-dev-functions-filter'),
        { auto: 0 }
      );
    }

    if ($('#loft-dev-elements-list')) {
      $('#loft-dev-elements-list').listSearchFilter(
        $('#loft-dev-elements-filter'),
        { auto: 0 }
      );
    }

    $('li .element-name a').click(function() {
      $(this)
        .parents('li')
        .find('.element-details')
        .slideToggle();
      return false;
    });

    // button catalog
    $('.button-catalog').once('button-catalog', function() {
      var $form = $(this).find('form'),
        $states = $form.find('.form-item-state select'),
        $layout = $form.find('.form-item-layout select'),
        $title = $form.find('.form-item-title input'),
        $class = $form.find('.form-item-class input'),
        $buttons = $(this).find('.button-catalog__components .button'),
        state = 'all',
        current = {};

      function applyClasses() {
        $buttons.each(function() {
          applyClass($(this));
        });
      }

      function applyClass($el) {
        $el.attr('class', $el.data('class'));
        if (current.state) {
          $el.addClass('is-' + current.state);
        }
        if (current.layout) {
          $el.addClass('layout--' + current.layout);
        }
        $el.addClass($class.val());
        if (!$title.val()) {
          $el.addClass('has-not-title');
        }
      }

      $buttons.each(function() {
        var $button = $(this);
        $button.data('class', $button.attr('class'));
        $button.click(function() {
          $button.show();
          state = state === 'all' ? 'one' : 'all';
          if (state === 'one') {
            $buttons.not($button).hide();
          } else {
            $buttons.show();
          }
          return false;
        });
      });
      $form.submit(function() {
        return false;
      });
      $class.keyup(function() {
        applyClasses();
      });
      $title.keyup(function() {
        $buttons.find('.button__text').text($title.val());
      });
      $states.change(function() {
        current.state = state = $(this).val();
        applyClasses();
      });
      $layout.change(function() {
        current.layout = $(this).val();
        applyClasses();
      });
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
    var settings = $.extend(
      {
        code: 13,
        auto: 6,
      },
      options
    );

    /**
     * Filter the list with a needle
     */
    var filter = function(needle) {
      var $items = $list.find('li');
      $items
        .hide()
        .filter(function() {
          return (
            $(this)
              .text()
              .indexOf(needle) !== -1
          );
        })
        .show();
    };

    /**
     * Handler of the input
     */
    $input.keypress(function(e) {
      var code = e.keyCode ? e.keyCode : e.which;
      var needle = $(this).val();
      if (
        (settings.auto && needle.length >= settings.auto) ||
        code === settings.code
      ) {
        if (needle) {
          filter(needle);
        } else {
          $list.find('li:hidden').show();
        }
      }
    });
    return $(this);
  };
})(jQuery);
