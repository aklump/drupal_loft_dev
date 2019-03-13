<?php
require_once dirname(__FILE__) . '/../vendor/autoload.php';

use Symfony\Component\Yaml\Yaml;

/**
 * @file
 * Integrates with drupal_deploy
 *
 * To enable this functionality you need to add something like this to your
 * local settings file:
 *
 * $conf['loft_dev_drupal_deploy_path'] = realpath(DRUPAL_ROOT .
 *   '/../drupal_deploy/user/deploy_5.0');
 */
function loft_dev_drupal_deploy_get_block($module, $delta) {
  $key = 'block--' . $module . '-' . $delta;
  if (($list = _loft_dev_drupal_deploy_get_files('blocks')) && isset($list[$key])) {
    $path = $list['block--' . $module . '-' . $delta]->uri;
    try {
      $data = Yaml::parse(file_get_contents($path));

      // First we take from a .html file
      $content = '';
      foreach (array('Body', 'body') as $key) {
        if (isset($data[$key])) {
          $content = isset($data[$key]['content']) ? $data[$key]['content'] : '';
          $filter = _loft_dev_drupal_deploy_get_filter($data[$key]);
          break;
        }
      }
      $html = preg_replace('/\.(yml|yaml)$/', '.html', $path);
      if (is_file($html)) {
        $content = file_get_contents($html);
      }

      $format = isset($filter->format) ? $filter->format : NULL;
      $content = check_markup($content, $format);
      // $content = $content ? token_replace($content) : '';

      $subject = '';
      foreach (array('Title', 'title', 'Subject', 'subject') as $key) {
        if (isset($data[$key])) {
          $subject = $data[$key];
          break;
        }
      }

      $block = array();
      if ($content) {
        $block = array(
          'subject' => $subject,
          'content' => $content,
        );
      }
    }
    catch (\Exception $e) {
      print $e->getMessage();
    }

    return $block;
  }
}

/**
 * Returns a filter array based on an item.
 *
 * @param  array $item
 *   Looking for a key format that is the format title or machine name.
 *
 * @return array
 */
function _loft_dev_drupal_deploy_get_filter($item) {
  foreach (array('format') as $key) {
    if (isset($item[$key])) {
      $filter_code = $item[$key];
      break;
    }
  }

  $filters = filter_formats();
  foreach ($filters as $filter) {
    if ($filter_code === $filter->name || $filter_code === $filter->format) {
      return $filter;
    }
  }

  return filter_default_format();
}

function _loft_dev_drupal_deploy_get_files($folder) {
  global $_loft_dev_drupal_deploy_caching;

  if (!($dir = variable_get('loft_dev_drupal_deploy_path', NULL))) {
    return array();
  }

  $caching = TRUE;

  if ($caching) {
    if ($cache = cache_get('loft_dev:' . __FUNCTION__, 'cache')) {
      $data = empty($cache->data) ? NULL : $cache->data;
    }
    else {
      // Set the default values
      $data = array();
    }
  }
  if (empty($data)) {
    $mask = '/.+\.yml$/';
    $data['blocks'] = file_scan_directory($dir . '/blocks', $mask, array('key' => 'name'));
    $data['nodes'] = file_scan_directory($dir . '/nodes', $mask, array('key' => 'name'));

    if ($caching) {
      cache_set('loft_dev:' . __FUNCTION__, $data, 'cache', CACHE_PERMANENT);
    }
  }

  return isset($data[$folder]) ? $data[$folder] : array();
}
