<?php
/**
 * @file
 * API documentation for loft_dev module.
 *
 * @addtogroup hooks
 * @{
 */

/**
 * Implements hook_loft_dev_js().
 *
 * Allow modules to easily disable entire groups of JS.
 */
function hook_loft_dev_js_alter(&$switches) {
  $switches['setting'] = 0;
  $switches['external'] = 0;
  $switches['core'] = 0;
  $switches['file.inline'] = 0;
  $switches['file.core'] = 0;
  $switches['file.contrib'] = 0;
  $switches['file.custom'] = 0;
  $switches['file.theme'] = 0;
}


/**
 * Implements hook_loft_dev_admin_stuff().
 *
 * Allow modules to add jquery selectors to what is considered admin stuff.
 * Such that they can affect the Hide Admin Stuff button.
 */
function hook_loft_dev_admin_stuff() {
  return array(
    'selectors' => array(
      ".links.inline",
      ".gop-admin-only",
    ),
  );
}

/**
 * Implements hook_loft_dev_menu
 *
 * Easily add links to the loft dev console
 *
 * @return array
 * This will be passed to theme_links
 * An array of arrays with:
 * - title: the visible link title
 * - href: the link to; this can be #
 *
 * @see theme_links()
 */
function hook_loft_dev_menu() {
  return array(
    array(
      'title' => '',
      'href' => '',
    ),
  );
}

/**
 * Implements hook_loft_dev_module_dependencies().
 *
 * Make sure all dependent modules get turned on when loft_dev is turned on. Use
 * this to indicate a suite of development modules that should be enabled when
 * you enable loft_dev. Add it to the core custom module of a site.
 *
 * @return array
 *   An array of module names that should be enabled when loft_dev is enabled
 */
function hook_loft_dev_module_dependencies() {
  return array(
    'ova_dev',
  );
}

/**
 * Implements hook_loft_dev_api().
 */
function hook_loft_dev_sandbox() {
  return array(
    // You may have more than one trigger...
    array(
      // Appending ?sb to the url will cause callback to be executed with
      // callback arguments.
      'query' => 'sb',
      'callback' => 'module_load_include',
      'callback arguments' => array(
        'inc',
        'my_module',
        'includes/my_module.sandbox',
      ),
    ),
  );
}

/**
 * Implements hook_loft_dev_button_catalog().
 */
function HOOK_loft_dev_button_catalog() {
  return [
    'sass_dir' => drupal_get_path('theme', 'gop_theme') . '/sass/drupal/',
    'sass_file' => '_button--catalog.scss',

    // A function that generates the build array for each button.
    'button_callback' => function ($title, $href, $theme, $state, $layout) {
      return array(
        '#theme' => 'button',
        '#title' => $title,
        '#href' => $href,
        '#button_type' => 'link',
        '#attributes' => new Attribute([
          'class' => [
            $theme ? 'theme--' . $theme : '',
            $state ? 'is-' . $state : '',
            $layout ? 'layout--' . $layout : '',
          ],
        ]),
      );
    },

    // Modules are special themes which also generate classnames like .button--primary
    // They should are meant to wrap up several themes to ease reuse.
    // You must also list your module in the themes array.
    'modules' => [
      'primary',
      'secondary',
      'tertiary',
      'token',
      'primary--facebook',
      'user-action',
    ],

    // Themes generate classnames like .button.theme--primary.
    // Themes are classes that can be applies as many as you want to a single .button.
    'themes' => [
      'add',
      'admin',
      'back',
      'black',
      'blue',
      'caps',
      'disabled',
      'facebook',
      'fadebook_share',
      'filter',
      'filters',
      'forward',
      'glyph',
      'goto',
      'green',
      'grey',
      'icon',
      'larger',
      'lesson-plan',
      'link',
      'mailto',
      'marked',
      'no-bg',
      'notes',
      'option',
      'outline',
      'parent',
      'pill',
      'pill-blue',
      'plus',
      'primary',
      'primary-red',
      'primary-white',
      'red',
      'secondary',
      'sharing',
      'sharp',
      'sharp-left',
      'short',
      'textfield',
      'trash',
      'tumblr',
      'twitter',
      'unmarked',
      'v--right',
      'white',
      'words',
      'words--black',
      'words--blue',
      'words--red',
    ],
    'states' => [
      'disabled',
      'error',
      'focus',
      'hidden',
      'inert',
      'selected',
      'success',
    ],
    'layouts' => ['center', 'right'],
  ];
}
