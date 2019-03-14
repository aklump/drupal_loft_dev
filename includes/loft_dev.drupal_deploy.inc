<?php

use Symfony\Component\Yaml\Yaml;

/**
 * @file
 * Integrates with drupal_deploy
 *
 * To enable this functionality you need to add something like this to your
 * local settings file:
 *
 * $conf['loft_dev_drupal_deploy_path'] = realpath(\Drupal::root() .
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
      foreach (['Body', 'body'] as $key) {
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
      foreach (['Title', 'title', 'Subject', 'subject'] as $key) {
        if (isset($data[$key])) {
          $subject = $data[$key];
          break;
        }
      }

      $block = [];
      if ($content) {
        $block = [
          'subject' => $subject,
          'content' => $content,
        ];
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
  foreach (['format'] as $key) {
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

  if (!($dir = \Drupal::config('loft_dev.settings')
    ->get('loft_dev_drupal_deploy_path'))) {
    return [];
  }

  $caching = TRUE;

  if ($caching) {
    if ($cache = \Drupal::cache('cache')->get('loft_dev:' . __FUNCTION__)) {
      $data = empty($cache->data) ? NULL : $cache->data;
    }
    else {
      // Set the default values
      $data = [];
    }
  }
  if (empty($data)) {
    $mask = '/.+\.yml$/';
    $data['blocks'] = file_scan_directory($dir . '/blocks', $mask, ['key' => 'name']);
    $data['nodes'] = file_scan_directory($dir . '/nodes', $mask, ['key' => 'name']);

    if ($caching) {
      \Drupal::cache('cache')
        ->set('loft_dev:' . __FUNCTION__, $data, \Drupal\Core\Cache\Cache::PERMANENT);
    }
  }

  return isset($data[$folder]) ? $data[$folder] : [];
}
