<?php
/**
 * @file
 * API documentation for loft_dev module.
 *
 * @addtogroup hooks
 * @{
 */

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
       within file path
 */
function hook_loft_dev_function_includes() {
  return array(
    array(
      'file path' => drupal_get_path('module', 'koiros') . '/includes',
      'file' => array(
        'koiros.trade.inc',
        'koiros.theme.inc',
      ),
    )
  );
}

/** @} */ //end of group hooks
