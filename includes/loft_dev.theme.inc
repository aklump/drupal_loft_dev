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
    \Drupal::configFactory()->getEditable('loft_dev.settings')->set('loft_dev_migration_urls_results', $vars['results'])->save();
  }
}

function loft_dev_check_path($path) {
  $parse = parse_url(trim($path));
  $uri = $parse['path'];
  $status = FALSE;
  // @FIXME
// menu_get_item() has been removed. To retrieve route information, use the
// RouteMatch object, which you can retrieve by calling \Drupal::routeMatch().
// 
// 
// @see https://www.drupal.org/node/2203305
// if ($item = menu_get_item($uri)) {
//     $status = !empty($item['path']);
//   }
//   elseif (($normal = drupal_get_normal_path($uri))
//     && $normal !== $uri
//     && ($item = menu_get_item($normal))) {
//     $status = !empty($item['path']);
//   }


  if (!$status) {
    // @FIXME
// url() expects a route name or an external URI.
// $url = url($uri, array('absolute' => TRUE));

    // @FIXME
// drupal_http_request() has been replaced by the Guzzle HTTP client, which is bundled
// with Drupal core.
// 
// 
// @see https://www.drupal.org/node/1862446
// @see http://docs.guzzlephp.org/en/latest
// $item = drupal_http_request($url, array(
//       'max_redirects' => 0,
//       'timeout' => 10,
//     ));

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
  $canonical = \Drupal::config('loft_dev.settings')->get('loft_dev_migration_canonical');
  foreach ($vars['results'] as $result) {
    $path = $result->path;
    if ($canonical) {
      // @FIXME
// l() expects a Url object, created from a route name or external URI.
// $path = l($path, $canonical . '/' . $path);

    }
    // @FIXME
// l() expects a Url object, created from a route name or external URI.
// $row = array(
//       $path,
//       $result->status ? t('migrated') : t('?'),
//       $result->status ? l($result->path, $result->path) : '?',
//       l(t('Add redirect'), 'admin/config/search/redirect/add', array(
//         'query' => drupal_get_destination() + array(
//             'source' => $result->path,
//           ),
//       )),
//     );

    $rows[$result->status][] = array(
      'data' => $row,
      'class' => array($result->status ? '' : 'error'),
    );
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
  $output = '<div' . drupal_attributes($vars['attributes']) . '><div class="border"><div class="padding">' . \Drupal::service("renderer")->render($build) . '</div></div></div>';

  return $output;
}

/**
 * Provides output for a solid css circle.
 *
 * @param array $vars
 *   $width
 *   $color
 *   $tag
 *   $attributes
 *
 * @return string
 *
 * @ingroup themeable
 */
function theme_loft_dev_css_circle($vars) {
  preg_match('/(\d+)(.*)/', $vars['width'], $matches);
  $w = $matches[1] / 2 . (empty($matches[2]) ? 'px' : $matches[2]);
  $style = array();
  $style[] = '-webkit-border-radius:' . $w;
  $style[] = '-moz-border-radius:' . $w;
  $style[] = 'border-radius:' . $w;
  $style[] = 'width:0';
  $style[] = 'height:0';
  $style[] = 'vertical-align:middle';
  $style[] = 'display:inline-block';
  $style[] = 'border:' . $w . ' solid ' . $vars['color'];
  $style = implode(';', $style);
  $attributes = \Drupal\Component\Utility\NestedArray::mergeDeep(array(
    'class' => array('circle'),
    'style' => $style,
  ), $vars['attributes']);

  $build[] = array(
    '#theme' => 'html_tag',
    '#tag' => $vars['tag'],
    '#attributes' => $attributes,
    '#value' => '',
  );

  $output = \Drupal::service("renderer")->render($build);

  return $output;
}
