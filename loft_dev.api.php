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
 * - href: the link to
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

/** @} */ //end of group hooks
