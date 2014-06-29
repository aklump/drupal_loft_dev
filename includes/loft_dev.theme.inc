<?php
/**
 * @file
 * Provides theme functions for loft_dev.
 *
 * @ingroup loft_dev
 * @{
 */

/**
 * Implements hook_preprocess_loft_dev_migration().
 *
 * @see  loft_dev_migration_urls_form().
 */
function loft_dev_preprocess_loft_dev_migration(&$vars) {

  //@todo This is an unconventional way to cache this; make better.
  if (empty($vars['results'])) {
    $vars['results'] = array();
    foreach ($vars['urls'] as $uri) {
      $vars['results'][$uri] = loft_dev_check_path($uri);
    }
    variable_set('loft_dev_migration_urls_results', $vars['results']);
  }
}

function loft_dev_check_path($path) {
  $parse = parse_url(trim($path));
  $uri = $parse['path'];
  $status = FALSE;
  if ($item = menu_get_item($uri)) {
    $status = !empty($item['path']);
  }
  elseif (($normal = drupal_get_normal_path($uri))
    && $normal !== $uri
    && ($item = menu_get_item($normal))) {
    $status = !empty($item['path']);
  }

  if (!$status) {
    $url = url($uri, array('absolute' => TRUE));
    $item = drupal_http_request($url, array('max_redirects' => 0, 'timeout' => 10));
    unset($item->response);
    $status = in_array(substr($item->code, 0, 1), array(2, 3));
  }

  return (object) array(
    'path' => $path,
    'uri' => $uri,
    'status' => $status,
    'item' => $item,
  );
}

/**
 * Formats the migration status.
 *
 * @param array $vars
 *
 * @return string
 *
 * @ingroup themeable
 */
function theme_loft_dev_migration($vars) {
  $build = array();

  $rows = array();
  $canonical = variable_get('loft_dev_migration_canonical', '');
  foreach ($vars['results'] as $result) {
    $path = $result->path;
    if ($canonical) {
      $path = l($path, $canonical . '/' . $path);
    }
    $row = array(
      $path,
      $result->status ? t('migrated') : t('?'),
      $result->status ? l($result->path, $result->path) : '?',
      l(t('Add redirect'), 'admin/config/search/redirect/add', array('query' => drupal_get_destination() + array(
        'source' => $result->path,
      ))),
    );
    $rows[$result->status][] = array('data' => $row, 'class' => array($result->status ? '' : 'error'));
  }

  $build['table'] = array(
    '#theme' => 'table',
    '#header' => array(
      t('Old Site'),
      t('Status'),
      t('New Site'),
      t('Op'),
    ),
    '#rows' => array_merge($rows[0], $rows[1]),
  );

  // Wrap it all up
  $vars['attributes']['class'][] = 'loft-dev-migration';
  $output = '<div' . drupal_attributes($vars['attributes']) . '><div class="border"><div class="padding">' . drupal_render($build) . '</div></div></div>';

  return $output;
}