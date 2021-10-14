<?php

/**
 * @file
 * Provide pages for loft_dev.
 */

use AKlump\LoftLib\Bash\Bash;
use Drupal\loft_dev\ButtonCatalog;

/**
 * Execute loft_deploy export via shell.
 *
 * @param string $basename
 *   The arg to pass to ld export.
 *
 * @return bool
 *   True if the backup succeeded.  False otherwise.
 */
function loft_dev_loft_deploy_export($basename) {
  $web_root = \Drupal::root();
  $purge_days = \Drupal::config('loft_dev.settings')
    ->get('loft_deploy_purge_after_days');
  $which_loft_deploy = \Drupal::config('loft_dev.settings')
    ->get('which_loft_deploy');
  $save_as = $basename . '_' . date_create('now')->format('Y-m-d_Hi');
  try {
    $home = Bash::exec('echo ~');
    Bash::exec([
      "export HOME=$home;",
      "cd $web_root &&",
      $which_loft_deploy,
      "export $save_as -fy",
      // This causes to run in background.
      "> /dev/null 2>&1 &",
    ]);

    if ($purge_days) {
      Bash::exec([
        "export HOME=$home;",
        "cd $web_root &&",
        $which_loft_deploy,
        "export-purge $purge_days -y",
        // This causes to run in background.
        "> /dev/null 2>&1 &",
      ]);
    }
  }
  catch (\Exception $exception) {
    return FALSE;
  }

  return TRUE;
}

/**
 * Generates the overview page
 */
function loft_dev_page() {
  $output = '';
  $output .= check_markup(file_get_contents(drupal_get_path('module', 'loft_dev') . '/README.txt'), 'plain_text');

  return $output;
}

/**
 * get a dummy array
 *
 * @param $count          int
 *                        The number of elements in the array
 * @param $multi_dim      int
 *                        The length of the multi dim array
 * @param $element_length int
 *                        How many words in each element
 */
function _loft_dev_dummy_array($count, $multi_dim = 0, $element_length = 1) {
  $array = array();
  for ($i = 0; $i < $count; ++$i) {
    if ($multi_dim) {
      $array[] = _loft_dev_dummy_array($multi_dim);
    }
    else {
      $array[] = _loft_dev_dummy_string($element_length);
    }
  }

  return $array;
}

function _loft_dev_dummy_string($length) {
  $latin = array(
    'lorem',
    'ipsum',
    'dolor',
    'sit',
    'amet',
    'consectetur',
    'adipisicing',
    'elit,',
    'sed',
    'do',
    'eiusmod',
    'tempor',
    'incididunt',
    'ut',
    'labore',
    'et',
    'dolore',
    'magna',
    'aliqua',
    'ut',
    'enim',
    'ad',
    'minim',
    'veniam',
    'quis',
    'nostrud',
    'exercitation',
    'ullamco',
    'laboris',
    'nisi',
    'ut',
    'aliquip',
    'ex',
    'ea',
    'commodo',
    'consequat',
    'duis',
    'aute',
    'irure',
    'dolor',
    'in',
    'reprehenderit',
    'in',
    'voluptate',
    'velit',
    'esse',
    'cillum',
    'dolore',
    'eu',
    'fugiat',
    'nulla',
    'pariatur',
    'excepteur',
    'sint',
    'occaecat',
    'cupidatat',
    'non',
    'proident',
    'sunt',
    'in',
    'culpa',
    'qui',
    'officia',
    'deserunt',
    'mollit',
    'anim',
    'id',
    'est',
    'laborum',
  );
  $word = array();
  while (count($word) < $length) {
    $word[] = $latin[rand(0, count($latin) - 1)];
  }

  return implode(' ', $word);
}

/**
 * Generate a true 404 page where the active menu item is blank
 */
function drupal_not_found_page() {
  // @FIXME
  // The active trail system has been removed in Drupal 8 because the routing and
  // linking systems have been completely rewritten. You will need to rewrite this
  // code to use the menu.active_trail service, or override the service if you need
  // to alter the active trail.
  //
  //
  // @see https://www.drupal.org/node/2240003
  // menu_set_active_item('page/not/found');


  return drupal_not_found();
}

/**
 * Generate a page of all node type teasers
 */
function loft_dev_teasers_page() {
  $build = array();
  // @FIXME
  // drupal_set_title() has been removed. There are now a few ways to set the title
  // dynamically, depending on the situation.
  //
  //
  // @see https://www.drupal.org/node/2067859
  // drupal_set_title(t('All Node Teasers Test Page'));

  foreach (loft_dev_node_suite() as $type => $nid) {
    $node = \Drupal::entityManager()->getStorage('node')->load($nid);
    $build[] = array('#markup' => '<h2>' . $type . '</h2>');
    if (!node_access('view', $node)) {
      $build[] = array('#markup' => t('Access Denied'));
    }
    else {
      $build[] = node_view($node, 'teaser');
    }
    $build[] = array('#markup' => '<hr />');
  }

  return $build;
}

/**
 * Sorting function for functions
 */
function _loft_dev_func_sort($a, $b) {
  $a = strip_tags($a);
  $a = trim($a, '_');
  $b = strip_tags($b);
  $b = trim($b, '_');
  if ($a == $b) {
    return 0;
  }

  return $a < $b ? -1 : 1;
}

/**
 * Render the REM font sizing page
 */
function loft_dev_rem_page($base = 16) {

  $sizes = '';
  for ($i = 1; $i <= 32; $i++) {
    $rem = round($i / $base, 4);
    $sizes[] = array($rem, $i);
  }
  $build[] = array(
    '#theme' => 'table',
    '#rows' => $sizes,
    '#header' => array('rem', 'px'),
  );
  drupal_add_http_header('Content-Type', 'text/html; charset=utf-8');
  print \Drupal::service("renderer")->render($build);
  drupal_exit();
}

/**
 * Form builder for the loft_dev_parse_time_form form.
 *
 * Accept a string and parse the english time into unix
 *
 * @param array $form
 * @param array &$form_state
 *
 * @see     loft_dev_parse_time_form_validate()
 * @see     loft_dev_parse_time_form_submit()
 * @ingroup forms
 */
function loft_dev_parse_time_form($form, &$form_state) {

  if (!empty($form_state['storage']['output'])) {
    //$form['output'] = array(
    //  '#type' => 'textarea',
    //  '#title' => t('Output'),
    //  '#default_value' => $form_state['storage']['output'],
    //  '#rows' => 20,
    //);
    $form['output'] = array(
      '#markup' => '<textarea>' . $form_state['storage']['output'] . '</textarea>',
    );
  }

  $form['input'] = array(
    '#type' => 'textarea',
    '#description' => t('Paste a string containing english time here'),
    '#title' => t('Input String'),
    '#default_value' => '',
    '#required' => TRUE,
    '#rows' => 20,
  );

  $form['time_out'] = array(
    '#type' => 'select',
    '#title' => t('Time Output Format'),
    '#default_value' => 'unix',
    '#options' => array(
      'unix' => 'Unix Timestamp',
    ),
  );

  $form['append_to_line'] = array(
    '#type' => 'checkbox',
    '#title' => t('Append to the end of the line'),
    '#default_value' => \Drupal::config('loft_dev.settings')
      ->get('loft_dev_parse_time:append_to_line'),
  );

  //http://api.drupal.org/api/drupal/includes%21common.inc/function/drupal_process_states/7
  $form['append_options'] = array(
    '#type' => 'container',
    '#states' => array(
      'visible' => array(
        ':input[name=append_to_line]' => array('value' => 1),
      ),
    ),
  );

  //@todo fix; not hiding
  $form['append_options']['append_prefix'] = array(
    '#type' => 'textfield',
    '#description' => t('When appending the output time, place this string between the line and the output.'),
    '#title' => t('Append Prefix'),
    '#default_value' => \Drupal::config('loft_dev.settings')
      ->get('loft_dev_parse_time:append_prefix'),
    '#size' => 10,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Parse Now'),
  );

  return $form;
}

/**
 * Form submission handler for loft_dev_parse_time_form().
 *
 * @see loft_dev_parse_time_form()
 * @see loft_dev_parse_time_form_validate()
 */
function loft_dev_parse_time_form_submit($form, &$form_state) {
  $output = array();
  $eol = "\n";
  $tok = strtok($form_state['values']['input'], $eol);
  while ($tok != FALSE) {
    if ($time = _loft_dev_pull_time_string($tok)) {
      if ($form_state['values']['append_to_line']) {
        $output[] = rtrim($tok) . $form_state['values']['append_prefix'] . $time;
      }
      else {
        $output[] = $time;
      }
    }
    else {
      drupal_set_message(t('No date found in: @line', array(
        '@line' => $tok,
      )), 'warning', FALSE);
      $output[] = $tok;
    }
    $tok = strtok($eol);
  }
  $form_state['rebuild'] = TRUE;
  $form_state['storage']['output'] = implode($eol, $output);

  \Drupal::configFactory()
    ->getEditable('loft_dev.settings')
    ->set('loft_dev_parse_time:append_prefix', $form_state['values']['append_prefix'])
    ->save();
  \Drupal::configFactory()
    ->getEditable('loft_dev.settings')
    ->set('loft_dev_parse_time:append_to_line', $form_state['values']['append_to_line'])
    ->save();
}

function _loft_dev_pull_time_string($string) {
  if (preg_match('/((?:(jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec)|(january|february|march|april|may|june|july|august|september|october|november|december))\s+[\sa-z0-9,]+)/i', $string, $matches)) {
    return strtotime($matches[1]);
  }

  return FALSE;
}

function loft_dev_migration_page() {
  $build = array();

  // @FIXME
  // Could not extract the default value because it is either indeterminate, or
  // not scalar. You'll need to provide a default value in
  // config/install/loft_dev.settings.yml and config/schema/loft_dev.schema.yml.
  $default = \Drupal::config('loft_dev.settings')
    ->get('loft_dev_migration_urls');
  if ($default) {
    // @FIXME
    // Could not extract the default value because it is either indeterminate, or
    // not scalar. You'll need to provide a default value in
    // config/install/loft_dev.settings.yml and config/schema/loft_dev.schema.yml.
    $build['current_status'] = array(
      '#theme' => 'loft_dev_migration',
      '#urls' => $default,
      '#results' => \Drupal::config('loft_dev.settings')
        ->get('loft_dev_migration_urls_results'),
    );
  }

  $build['form'] = \Drupal::formBuilder()
    ->getForm('loft_dev_migration_urls_form', $default);

  return $build;
}

/**
 * Form builder for the loft_dev_migration_urls_form form.
 *
 * Input and process the migration urls from a previous site.
 *
 * @param array $form
 * @param array &$form_state
 *
 * @see     loft_dev_migration_urls_form_validate()
 * @see     loft_dev_migration_urls_form_submit()
 * @ingroup forms
 */
function loft_dev_migration_urls_form($form, &$form_state, $default) {
  $form['loft_dev_migration_canonical'] = array(
    '#type' => 'textfield',
    '#description' => t('Enter the base url of the current production site.'),
    '#title' => t('Canonical URL'),
    '#default_value' => \Drupal::config('loft_dev.settings')
      ->get('loft_dev_migration_canonical'),
    '#required' => TRUE,
  );

  $form['loft_dev_migration_urls'] = array(
    '#type' => 'textarea',
    '#title' => t('Expected URLs from previous website'),
    '#description' => t('Enter all relative urls from the old website that you wish to assert exist in this, one per line.'),
    '#rows' => 20,
    '#resizable' => TRUE,
    '#default_value' => implode(PHP_EOL, $default),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save/Check Status'),
  );

  return $form;
}

/**
 * Form submission handler for loft_dev_migration_urls_form().
 *
 * @see loft_dev_migration_urls_form()
 * @see loft_dev_migration_urls_form_validate()
 */
function loft_dev_migration_urls_form_submit($form, &$form_state) {

  \Drupal::configFactory()
    ->getEditable('loft_dev.settings')
    ->set('loft_dev_migration_canonical', trim($form_state['values']['loft_dev_migration_canonical'], '/'))
    ->save();
  \Drupal::config('loft_dev.settings')
    ->clear('loft_dev_migration_urls_results')
    ->save();

  if ($urls = trim($form_state['values']['loft_dev_migration_urls'])) {
    $urls = explode(PHP_EOL, $urls);
    $urls = array_unique($urls);
    sort($urls);
    foreach ($urls as $key => $value) {
      $urls[$key] = trim($value);
    }
    \Drupal::configFactory()
      ->getEditable('loft_dev.settings')
      ->set('loft_dev_migration_urls', $urls)
      ->save();
  }
}

/**
 * Form builder for the loft_dev_css_aggregation_form form.
 *
 * Interrupts which files get aggregated to debug issues.
 *
 * @param array $form
 * @param array &$form_state
 *
 * @see     loft_dev_css_aggregation_form_validate()
 * @see     loft_dev_css_aggregation_form_submit()
 * @ingroup forms
 */
function loft_dev_css_aggregation_form($form, &$form_state) {
  // @FIXME
  // Could not extract the default value because it is either indeterminate, or
  // not scalar. You'll need to provide a default value in
  // config/install/loft_dev.settings.yml and config/schema/loft_dev.schema.yml.
  $default_value = \Drupal::config('loft_dev.settings')
    ->get('loft_dev_css_files_omit');
  // @FIXME
  // Could not extract the default value because it is either indeterminate, or
  // not scalar. You'll need to provide a default value in
  // config/install/loft_dev.settings.yml and config/schema/loft_dev.schema.yml.
  $options = \Drupal::config('loft_dev.settings')
    ->get('loft_dev_css_files_options');
  $form['loft_dev_css_files_omit'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Omit these files from aggregation'),
    '#default_value' => $default_value,
    '#options' => $options,
  );

  return system_settings_form($form);

  return $form;
}

/**
 * Form validation handler for loft_dev_css_aggregation_form().
 *
 * @see loft_dev_css_aggregation_form()
 * @see loft_dev_css_aggregation_form_submit()
 */
function loft_dev_css_aggregation_form_validate($form, &$form_state) {
  $form_state['values']['loft_dev_css_files_omit'] = array_filter($form_state['values']['loft_dev_css_files_omit']);
}

function loft_dev_button_catalog_page($theme = NULL) {

  $caching = empty($theme) && 0;
  if ($caching) {
    if ($cache = \Drupal::cache('cache')->get('loft_dev:button_catalog')) {
      $data = empty($cache->data) ? NULL : $cache->data;
    }
    else {
      // Set the default values
      $data = array();
    }
  }
  if (empty($data)) {
    try {

      // Calculate the value of $data now...
      $config = \Drupal::moduleHandler()->invokeAll('loft_dev_button_catalog');
      $obj = new ButtonCatalog($config);
      $data = $obj->setTheme($theme)->writeSass()->build();
    }
    catch (\Exception $exception) {
      drupal_set_message($exception->getMessage(), 'error', FALSE);
    }
    $data = \Drupal::service("renderer")->render($data);

    if ($caching) {
      \Drupal::cache('cache')
        ->set('loft_dev:button_catalog', $data, CACHE_TEMPORARY);
    }
  }

  return $data;
}
