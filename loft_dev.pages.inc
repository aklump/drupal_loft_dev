<?php
/**
 * @file
 * Pages for loft_dev
 */

/**
 * Generates the overview page
 */
function loft_dev_page() {
  $output = '';
  $output .= check_markup(file_get_contents(drupal_get_path('module', 'loft_dev') .'/README.txt'), 'plain_text');
  return $output;
}

/**
 * Generates a page with lots of markup to test your theme
 */
function loft_dev_theme_test_page() {

  //set some messages
  drupal_set_message(_loft_dev_dummy_string(20), 'status');
  drupal_set_message(_loft_dev_dummy_string(20), 'warning');
  drupal_set_message(_loft_dev_dummy_string(20), 'error');
  drupal_set_message(_loft_dev_dummy_string(20), 'status');
  drupal_set_message(_loft_dev_dummy_string(20), 'warning');

  $output = '';

  //headings
  for ($i = 0; $i < 6; ++$i) {
    $output .= '<h'. ($i+1) .'>&lt;h'. ($i+1) .'> '. _loft_dev_dummy_string(5) .'</h'. ($i+1) .'>'."\n";
  }

  $output .= '<strong>&lt;strong> '. _loft_dev_dummy_string(4).'</strong>'."\n";

  $output .= '<a href="#" onclick="return: false;">&lt;a> '. _loft_dev_dummy_string(3) .'</a>'."\n";

  $output .= '<em>&lt;em> '. _loft_dev_dummy_string(4).'</em>'."\n";

  $output .= '<code>&lt;code> '. _loft_dev_dummy_string(10) .'</code>'."\n";

  $output .= '<div>'."\n";
  $output .= _loft_dev_dummy_string(5) .'<sub>&lt;sub> '. _loft_dev_dummy_string(3) .'</sub>'."\n";

  $output .= _loft_dev_dummy_string(20) .'<sup>&lt;sup> '. _loft_dev_dummy_string(3) .'</sup>'. _loft_dev_dummy_string(20). "\n";

  $output .= '</div>'."\n";

  $output .= '<pre>&lt;pre>10 print "Hello World"' . "\n" . '20 goto 10</pre>' . "\n";

  //ordered list
  $output .= theme('item_list', array(
    'items' => _loft_dev_dummy_array(5, NULL, 20),
    'title' => '&lt;ol> '. _loft_dev_dummy_string(4),
    'type'  => 'ol',
  )) . "\n";

  //unordered list
  $output .= theme('item_list', array(
    'items' => _loft_dev_dummy_array(5, NULL, 20),
    'title' => '&lt;ul> '. _loft_dev_dummy_string(4),
    'type'  => 'ul',
  )) . "\n";

  //p tags
  $output .= '<p>p tag: Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>'."\n";

  $output .= '<blockquote>blockquote tag: Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla at massa sed nulla consectetur malesuada.</blockquote>' . "\n";

  $output .= '<p>p tag: Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>'."\n";

  //hr
  $output .= '<hr />' . "\n";

  $output .= '<p>p tag: Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>'."\n";

  //table
  $rows = _loft_dev_dummy_array(10, 10);

  // Make first row links, so we theme links in table
  foreach ($rows[0] as $cell_key => $cell) {
    $rows[0][$cell_key] = '<a href="#" onclick="return false;">' . $cell . '</a>';
  }
  $output .= theme('table', array(
    'header' => _loft_dev_dummy_array(10),
    'rows' => $rows,
  )) . "\n";



  // Throbber
  $output .= '<div><div class="ajax-progress">
    <div class="throbber"></div>
  </div></div>' . "\n";


  //form
  $output .= drupal_render(drupal_get_form('test_form_form')) ."\n";

  //confirm form
  //@todo fix this; wasn't working on gop3 - aklump 05/08/2012 20:21:46
  //$form = array();
  //$output .= '<h3>Confirm Form</h3>' . "\n";
  //$confirm = confirm_form($form, _loft_dev_dummy_string(5) . '?', '<front>', _loft_dev_dummy_string(26));
  //$output .= drupal_render($confirm);

  $output .= str_repeat(theme('image', array(
    'path' => drupal_get_path('module', 'loft_dev') . '/images/monalisa.jpg',
    //_loft_dev_dummy_string(4), _loft_dev_dummy_string(8)) ."\n";
  )), 3);

  //pager
  global $pager_page_array, $pager_total;
  $pager_page_array = array(empty($_GET['page']) ? 0 : $_GET['page']);
  $pager_total = array(100);
  $output .= theme('pager') ."\n";

  return $output;
}

/**
 * get a dummy array
 *
 * @param $count int
 *   The number of elements in the array
 * @param $multi_dim int
 *   The length of the multi dim array
 * @param $element_length int
 *   How many words in each element
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
  $latin = array('lorem','ipsum','dolor','sit','amet','consectetur','adipisicing','elit,','sed','do','eiusmod','tempor','incididunt','ut','labore','et','dolore','magna','aliqua','ut','enim','ad','minim','veniam','quis','nostrud','exercitation','ullamco','laboris','nisi','ut','aliquip','ex','ea','commodo','consequat','duis','aute','irure','dolor','in','reprehenderit','in','voluptate','velit','esse','cillum','dolore','eu','fugiat','nulla','pariatur','excepteur','sint','occaecat','cupidatat','non','proident','sunt','in','culpa','qui','officia','deserunt','mollit','anim','id','est','laborum');
  $word = array();
  while (count($word) < $length) {
    $word[] = $latin[rand(0, count($latin) - 1)];
  }
  return implode(' ', $word);
}

/**
 * Form builder for the test_form form.
 *
 * This is an example of a form for theme testing
 *
 * @see test_form_form_validate()
 * @see test_form_form_submit()
 * @ingroup forms
 */
function test_form_form($form_state) {
  $form = array();

  $form['#attributes']['onsubmit'] = 'return false;';

  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => _loft_dev_dummy_string(3),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['fieldset']['text'] = array(
    '#type' => 'textfield',
    '#description' => _loft_dev_dummy_string(10),
    '#title' => _loft_dev_dummy_string(3),
    '#required' => TRUE,
    '#size' => 60,
    '#autocomplete_path' => 'user/autocomplete',
  );

  $form['fieldset']['text2'] = array(
    '#type' => 'textfield',
    '#description' => _loft_dev_dummy_string(10),
    '#title' => _loft_dev_dummy_string(3),
    '#required' => TRUE,
    '#size' => 60,
  );
  $form['fieldset']['checkboxes'] = array(
    '#type' => 'checkboxes',
    '#title' => _loft_dev_dummy_string(4),
    '#options' => _loft_dev_dummy_array(3),
    '#description' => _loft_dev_dummy_string(8),
  );

  $form['fieldset']['date'] = array(
    '#type' => 'date',
    '#title' => _loft_dev_dummy_string(3),
    '#description' => _loft_dev_dummy_string(8),
    '#required' => TRUE,
  );

  $form['fieldset']['comment_preview'] = array(
    '#type' => 'radios',
    '#title' => _loft_dev_dummy_string(3),
    '#default_value' => 0,
    '#options' => _loft_dev_dummy_array(3),
    '#description' => _loft_dev_dummy_string(8),
  );

  $form['fieldset']['body'] = array(
    '#type' => 'textarea',
    '#title' => _loft_dev_dummy_string(3),
    '#description' => _loft_dev_dummy_string(8),
  );

  $form['fieldset']['upload'] = array(
    '#type' => 'file',
    '#title' => _loft_dev_dummy_string(4),
    '#description' => _loft_dev_dummy_string(8),
  );

  $form['fieldset']['submit'] = array(
    '#type' => 'submit',
    '#value' => _loft_dev_dummy_string(3),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Form validation handler for test_form_form().
 *
 * @see test_form_form()
 * @see test_form_form_submit()
 */
function test_form_validate($form, &$form_state) {
  if ($form_state['values']['name'] == '') {
    form_set_error('', t('You must select a name for this group of settings.'));
  }
}

/**
 * Form submission handler for user_login_form().
 *
 * @see test_form_form()
 * @see test_form_form_validate()
 */
function test_form_form_submit($form, &$form_state) {
  db_query("INSERT INTO {table} (name, log, hidden) VALUES ('%s', %d, '%s')", $form_state['values']['name'], $form_state['values']['access']['log'],  $form_state['values']['hidden']);
  drupal_set_message(t('Your form has been saved.'));
}

/**
 * Generate a true 404 page where the active menu item is blank
 */
function drupal_not_found_page() {
  menu_set_active_item('');
  return drupal_not_found();
}

/**
 * Generate a page of all node type teasers
 */
function loft_dev_teasers_page() {
  $build = array();
  drupal_set_title(t('All Node Teasers Test Page'));
  foreach (loft_dev_node_suite() as $type => $nid) {
    $node = node_load($nid);
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
 * Genereate the libraries list page
 */
function loft_dev_list_libraries_page() {
  $all = loft_dev_get_libraries();
  $rows = array();
  foreach ($all as $module => $libraries) {
    foreach ($libraries as $key => $data) {
      $title = empty($data['title']) ? $key : $data['title'];
      $link = empty($data['website']) ? $title : l($title, $data['website'], array(
        'attributes' => array(
          'onclick' => 'window.open(this.href); return false;',
        ),
      ));
      $rows[$key] = array(
        $link,
        $key,
        $module,
      );
    }
  }
  ksort($rows);
  $build = array();
  $build[] = array(
    '#theme' => 'table',
    '#rows' => $rows,
    '#header' => array(t('Library'), t('Machine'), t('Module')),
  );
  return $build;
}

/**
 * Genereate the libraries list page
 */
function loft_dev_list_fapi_elements_page() {
  $info_hook_modules = module_implements('element_info', TRUE);
  $elements = array();
  foreach ($info_hook_modules as $module) {
    $elements += module_invoke($module, 'element_info');
  }
  $items = array();
  foreach ($elements as $name => $data) {
    if ($name === 'machine_name') {
      continue;
    }

    if (isset($data['#theme_wrappers'])
        && in_array('form_element', (array) $data['#theme_wrappers'])) {
      $name = $name . ' (fapi)';
    }
    $item = '';
    $item .= '<div class="element-name"><a href="#" onclick="return false;">' . $name . '</a></div>';

    $details = var_export($data, TRUE);
    $details = str_replace('<', '&lt;', $details);
    $details = preg_replace('/=>\s+array/', '=> array', $details);
    $item .= '<div class="element-details"><pre>' . $details . '</pre></div>';
    $items[$name] = $item;
  }
  ksort($items);

  $build = array();

  // Create a textbox for jquery to user for filtering
  $build['filter'] = array(
    '#attributes' => array(
      'id' => 'loft-dev-elements-filter',
    ),
    '#type' => 'textfield',
    '#description' => t('Use this box to filter the list below'),
    '#title' => t('Filter'),
    '#default_value' => '',
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'loft_dev') . '/loft_dev.js',
      ),
    ),
  );

  $build[] = array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#attributes' => array(
      'id' => 'loft-dev-elements-list',
    ),
  );

  drupal_add_css(drupal_get_path('module', 'loft_dev') . '/loft_dev.css');
  drupal_add_js(drupal_get_path('module', 'loft_dev') . '/loft_dev.js');

  return $build;
}

function loft_dev_server_vars_page() {
  $build = array();

  $output = '<h2>$_SERVER</h2>';
  $output .= var_export($_SERVER, TRUE);
  $output = str_replace("\n", '<br />', $output);
  $build['server'] = array('#markup' => $output);

  if (!empty($_SESSION)) {
    $output = '<h2>$_SESSION</h2>';
    $output .= var_export($_SESSION, TRUE);
    $output = str_replace("\n", '<br />', $output);
    $build['session'] = array('#markup' => $output);
  }

  // Capture last 10 user agents
  $agents = variable_get('loft_dev_user_agents', array());
  if (!in_array($_SERVER['HTTP_USER_AGENT'], $agents)) {
    array_unshift($agents, $_SERVER['HTTP_USER_AGENT']);
    $agents = array_slice($agents, 0, 10);
    variable_set('loft_dev_user_agents', $agents);
  }
  $build['session_title'] = array('#markup' => '<h2>Recent Agents</h2>');
  $build['session'] = array(
    '#theme' => 'item_list',
    '#items' => $agents,
  );

  return $build;
}

function loft_dev_zebra_striping_page($max = 100) {
  drupal_add_css(drupal_get_path('module', 'loft_dev') . '/loft_dev.css');
  $build = $items = array();
  module_load_include('inc', 'loft_dev', 'includes/loft_dev.theme');
  loft_dev_zebra_stripes_reset('loft_dev_zebra_striping_page');
  for ($i = 0; $i < $max; ++$i) {
    $classes = array();
    loft_dev_zebra_stripes($classes, 'loft_dev_zebra_striping_page');
    $line = ' ' . implode(' ', $classes) . ' ';
    $line = str_replace(' alt ', ' <span class="alt">alt</span> ', $line);
    $line = str_replace(' tri ', ' <span class="tri">tri</span> ', $line);
    $line = str_replace(' tetra ', ' <span class="tetra">tetra</span> ', $line);
    $line = str_replace(' alpha ', ' <span class="alpha">alpha</span> ', $line);
    $line = str_replace(' beta ', ' <span class="beta">beta</span> ', $line);
    $line = str_replace(' gamma ', ' <span class="gamma">gamma</span> ', $line);
    $line = str_replace(' delta ', ' <span class="delta">delta</span> ', $line);
    $items[] = trim($line);
  }
  $build[] = array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#type' => 'ol',
  );
  return $build;
}

//@@details How to do zebra striping

/**
 * Add zebra striping to an classes array based on increment
 *
 * @param array &$classes_array
 *
 * @return NULL
 *
 * @see drupal_static_reset('gop3_zebra')
 */
function loft_dev_zebra_stripes(&$classes_array, $zebra_group = 'default') {

  //@todo Fine tune $column_classes as needed for your project

  // You should tune this to your project's needs...
  // If you want a four column display then you would set $column_classes =
  // array(4); If you want to be able to apply a 2,3,4,5 column display then set
  // $column_classes = array(2,3,4,5). And so fourth... By default we'll set
  // this up for 3 and 4 columns.
  $column_classes = array(3,4,5,6,7,8);
  // end config

  $word = array('zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine');
  $increment = &drupal_static('gop3_zebra', array());
  $classes_array = (array) $classes_array;

  // For running ordinal, e.g. first, second, third...
  $increment[$zebra_group]['running'] = empty($increment[$zebra_group]['running']) ? 1 : $increment[$zebra_group]['running'] + 1;

  $increment[$zebra_group]['odd'] = empty($increment[$zebra_group]['odd']) ? 1 : !$increment[$zebra_group]['odd'];

  $classes_array[] = _loft_dev_get_ordinal($increment[$zebra_group]['running']);
  $classes_array[] = $increment[$zebra_group]['odd'] ? 'odd' : 'even';

  // For every other (alt), every third (tri) and every fourth (tetra)
  if ($increment[$zebra_group]['running'] % 2 == 0) {
    $classes_array[] = 'alt';
  }
  if ($increment[$zebra_group]['running'] % 3 == 0) {
    $classes_array[] = 'tri';
  }
  if ($increment[$zebra_group]['running'] % 4 == 0) {
    $classes_array[] = 'tetra';
  }
  // For columns
  foreach ($column_classes as $i) {
    $increment[$zebra_group]['base_' . $i] = empty($increment[$zebra_group]['base_' . $i]) ? 1 : $increment[$zebra_group]['base_' . $i] + 1;
    if ($increment[$zebra_group]['base_' . $i] > $i) {
      $increment[$zebra_group]['base_' . $i] = 1;
    }

    $class = $word[substr($i, 0, 1)] . substr($i, 1);
    $class .= '-cols-';
    if ($increment[$zebra_group]['base_' . $i] == 1) {
      $class .= 'first';
    }
    elseif ($i == $increment[$zebra_group]['base_' . $i]) {
      $class .= 'last';
    }
    else {
      $class .= $increment[$zebra_group]['base_' . $i];
    }
    $classes_array[] = $class;
  }
}

/**
 * Return the ordinal word of a number up to 99
 *
 * @param int $number
 *
 * @return string
 */
function _loft_dev_get_ordinal($number) {
  $first_word = array('eth', 'first', 'second', 'third', 'fourth', 'fifth', 'sixth', 'seventh', 'eighth', 'ninth', 'tenth', 'eleventh', 'twelfth', 'thirteenth', 'fourteenth', 'fifteenth', 'sixteenth', 'seventeenth', 'eighteenth', 'nineteenth', 'twentieth');
  $second_word =array('', '', 'twenty', 'thirty', 'forty', 'fifty', 'sixty', 'seventy', 'eighty', 'ninty');
  if($number <= 20) {
    return $first_word[$number];
  }
  $first_num = substr($number, -1, 1);
  $second_num = substr($number, -2, 1);
  return $string = str_replace('y-eth', 'ieth', $second_word[$second_num] . '-' . $first_word[$first_num]);
}

/**
 * Reset zebra striping
 *
 * @param strings...
 *   Optional, keys of zebra groups to reset.  Leave blank to reset all
 *
 * @return NULL
 */
function loft_dev_zebra_stripes_reset() {
  $groups = func_get_args();
  if (empty($groups)) {
    drupal_static_reset('gop3_zebra');
  }
  else {
    $increment = &drupal_static('gop3_zebra', array());
    $increment = array_diff_key($increment, array_flip($groups));
  }
}

/**
 * Genereate the fpo page to be used to create images
 */
function loft_dev_fpo_image_page() {
  $output = '';
  $path = url(drupal_get_path('module', 'loft_dev') . '/images/fpo-bg.png');
  $output .= '<body style="width: 100%; height: 100%; background: url(' . $path . ') repeat"></body>' . "\n";
  print $output;
  drupal_exit();
}


/**
 * Generate the available site functions page
 */
function loft_dev_list_functions_page($op) {

  ini_set('memory_limit','192M');

  $output = '';

  /**
   * Load Explicit files
   */
  $includes = module_invoke_all('loft_dev_function_includes');
  foreach ($includes as $array) {
    $dir = DRUPAL_ROOT . '/' . $array['file path'] . '/';
    if (!is_array($array['file'])) {
      $array['file'] = array($array['file']);
    }
    foreach (element_children($array['file']) as $file) {
      if (is_file($dir . $file)) {
        require_once $dir . $file;
      }
    }
    if (!empty($array['file']['#mask']) &&
        ($files = file_scan_directory($dir, $array['file']['#mask']))) {
      foreach ($files as $file) {
        $file = drupal_realpath($file->uri);
        require_once $file;
      }
    }
  }

  /**
   * Auto load all .inc files for all active modules
   */
  $result = db_select('system', 's')
    ->fields('s', array('filename'))
    ->condition('status', '1')

    //@todo figure out why these cause trouble; has to do with classes
    ->condition('name', array('backup_migrate', 'date', 'metatag', 'print', 'prod_check', 'email', 'fb_social', 'imageapi', 'mailchimp', 'coder', 'comment_notify', 'link', 'commerce_product'), 'NOT IN')
    ->execute()->fetchCol();

  $skipped_files = array(
    'filters.backup_restore.inc',
    'filters.compression.inc',
    'commerce_product.translation_handler.inc',
    'rules_i18n.i18n.inc',
  );
  foreach ($result as $filename) {
    $dir = drupal_dirname($filename);
    $includes = file_scan_directory($dir, '/\.inc$/', array(
      'recurse' => TRUE,
    ));
    foreach ($includes as $file) {
      $file = drupal_realpath($file->uri);
      $info = pathinfo($file);
      if (!in_array($info['basename'], $skipped_files)
          && preg_match('/^<\?php/s', file_get_contents($file))) {
        require_once $file;
      }
    }
  }

  // Create a textbox for jquery to user for filtering
  $form['filter'] = array(
    '#attributes' => array(
      'id' => 'loft-dev-functions-filter',
    ),
    '#type' => 'textfield',
    '#description' => t('Use this box to filter the list below'),
    '#title' => t('Filter'),
    '#default_value' => '',
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'loft_dev') . '/loft_dev.js',
      ),
    ),
  );
  $output .= drupal_render($form) . "\n";

  $output .= '<ol id="loft-dev-functions-list">'."\n";

  $list = array();

  switch ($op) {
    case 'constants':
      $list = array();
      foreach (get_defined_constants() as $key => $value) {
        $list[] = "$key = $value";
      }
      break;
    case 'classes':
      $list = get_declared_classes();
      break;
    case 'functions':
      $functions = get_defined_functions();
      $list = array();
      foreach($functions['user'] as $function) {
        $list[] = "<a href='http://api.drupal.org/api/HEAD/function/$function' target='_blank'>$function</a>";
        //$list[trim($function, '_')] = "<a href='http://api.drupal.org/api/HEAD/function/$function' target='_blank'>$function</a>";
      }
      uasort($list, '_loft_dev_func_sort');
      break;
  }

  $output .= '<li>' .  implode("</li>\n<li>", $list) ."</li>\n";
  $output .= '</ol>'."\n";

  return $output;
}

/**
 * Sorting function for functions
 *
 * @see loft_dev_list_functions_page()
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
function loft_dev_rem_page() {
  $sizes = '';
  for ($i = 0; $i <= 2; $i+=.0625) {
    $sizes[] = round($i, 3);
  }
  drupal_add_http_header('Content-Type', 'text/html; charset=utf-8');
  $build = array(
    '#markup' => implode('<br />', $sizes),
  );
  print drupal_render($build);
  exit;
}

/**
 * Form builder for the loft_dev_parse_time_form form.
 *
 * Accept a string and parse the english time into unix
 *
 * @param array $form
 * @param array &$form_state
 *
 * @see loft_dev_parse_time_form_validate()
 * @see loft_dev_parse_time_form_submit()
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
    '#default_value' => variable_get('loft_dev_parse_time:append_to_line', TRUE),
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
    '#default_value' => variable_get('loft_dev_parse_time:append_prefix', '|'),
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

  variable_set('loft_dev_parse_time:append_prefix', $form_state['values']['append_prefix']);
  variable_set('loft_dev_parse_time:append_to_line', $form_state['values']['append_to_line']);
}

function _loft_dev_pull_time_string($string) {
  if (preg_match('/((?:(jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec)|(january|february|march|april|may|june|july|august|september|october|november|december))\s+[\sa-z0-9,]+)/i', $string, $matches)) {
    return strtotime($matches[1]);
  }

  return FALSE;
}
