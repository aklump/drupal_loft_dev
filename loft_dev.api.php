<?php
/**
 * @file
 * API documentation for loft_dev module.
 *
 * @addtogroup hooks
 * @{
 */

/**
 * Implements hook_loft_dev_admin_stuff().
 *
 * Allow modules to add jquery selectors to what is considered admin stuff.
 * Such that they can affect the Hide Admin Stuff button. 
 */
function hook_loft_dev_admin_stuff() {
  return array(
    'selectors' => {
      ".links.inline",
      ".gop-admin-only",
    }
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
 * Implements hook_loft_dev_function_includes().
 *
 * If you need to manually add files to the function lookup pages use this.
 *
 * @return array
 * - An array of arrays each with:
 *   - file path: the path to the file or files
 *   - file: string/array
 *     If you need to load more than one file, include an array of files all
 *     within file path
 *     If you want to use a regex mask and scan teh file_path then use: #mask
 *     @code
 *       array('#mask' => '/*\.inc$/')
 *     @endcode
 */

function hook_loft_dev_function_includes() {
  return array(
    array(
      'file path' => drupal_get_path('module', 'koiros') . '/includes',
      'file' => array(
        '#mask' => '/\.inc$/',
      ),
    )
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
    'ova_dev'
  );
}

/** @} */ //end of group hooks
