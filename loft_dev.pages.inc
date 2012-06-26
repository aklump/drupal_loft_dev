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
  $form = array();
  $output .= '<h3>Confirm Form</h3>' . "\n";
  $output .= drupal_render(confirm_form($form, NULL, '<front>', _loft_dev_dummy_string(26)));

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
 * Generate the available site functions page
 */
function loft_dev_list_functions_page() {
  $output = '';
  $output .= '<ol>'."\n";
  $functions = get_defined_functions();
  $sorted = array();
  foreach($functions['user'] as $function) {
    $sorted[trim($function, '_')] = "<li><a href='http://api.drupal.org/api/HEAD/function/$function' target='_blank'>$function</li>";
  }
  ksort($sorted);
  $output .= implode("\n", $sorted) ."\n";
  $output .= '</ol>'."\n";
  return $output;
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
  foreach (loft_dev_node_suite() as $type => $node) {
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
