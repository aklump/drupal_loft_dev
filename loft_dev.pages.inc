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
  drupal_set_message(_loft_dev_dummy_string(20), 'error');

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
  //ordered list
  $output .= theme('item_list', _loft_dev_dummy_array(5),  '&lt;ol> '. _loft_dev_dummy_string(4), 'ol')."\n";

  //unordered list
  $output .= theme('item_list', _loft_dev_dummy_array(5),  '&lt;ul> '. _loft_dev_dummy_string(4), 'ul')."\n";

  //p tags
  $output .= '<p>p tag: Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>'."\n";

  $output .= '<p>p tag: Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>'."\n";

  $output .= '<p>p tag: Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>'."\n";

  //table
  $output .= theme('table', _loft_dev_dummy_array(10), _loft_dev_dummy_array(10, 10)) ."\n";

  //form
  $output .= drupal_get_form('test_form_form') ."\n";

  $output .= theme('image', drupal_get_path('module', 'loft_dev') . '/image.jpg', _loft_dev_dummy_string(4), _loft_dev_dummy_string(8)) ."\n";


  //pager
  global $pager_page_array, $pager_total;
  $pager_page_array = array(1);
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
 */
function _loft_dev_dummy_array($count, $multi_dim = 0) {
  $array = array();
  for ($i = 0; $i < $count; ++$i) {
    if ($multi_dim) {
      $array[] = _loft_dev_dummy_array($multi_dim);
    }
    else {
      $array[] = _loft_dev_dummy_string(1);
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
