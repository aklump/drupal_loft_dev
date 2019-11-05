<?php

namespace Drupal\loft_dev\Plugin\migrate\process;

use Drupal\migrate\MigrateException;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\Row;

/**
 * Extract a value from XML by xpath.
 *
 * Available configuration keys:
 * - expression: The XPath expression.
 *
 * @MigrateProcessPlugin(
 *   id = "loft_xml_extract"
 * )
 *
 * The loft_xml_extract plugin pulls the value out of an XML string using an
 *   XPath selector and returns it as an array.  Each value of the array is the
 *   node value cast to a string.  For non-string source values you may use the
 *   get plugin as shown in the example  Also use in conjunction with the
 *   extract plugin as shown below, or the flatten plugin to flatten.
 *
 * @code
 * process:
 *   'field_subtitle/0/value':
 *     - plugin: loft_xml_extract
 *       source: 'field_xml_metadata/0/xml'
 *       expression: '/page/header'
 *     - plugin: skip_on_empty
 *       method: row
 *     - plugin: extract
 *       index: [0]
 * @endcode
 *
 * @link https://codebeautify.org/Xpath-Tester
 * @link https://www.w3schools.com/xml/xpath_syntax.asp
 * @link https://www.php.net/manual/en/simplexml.examples-basic.php
 */
class LoftXmlExtract extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    $new_value = [];
    // Require strings, but also allow NULL so that an incoming empty from the
    // get plugin does not indicate that this plugin has failed.
    if (!is_null($value) && !is_string($value)) {
      throw new MigrateException('Input must be a string or NULL.');
    }

    if (!empty($value)) {
      if (!($loaded = simplexml_load_string($value))) {
        throw new MigrateException('The input value cannot be understood as XML.');
      }
      $node = $loaded->xpath($this->configuration['expression']);
      foreach ($node as $item) {
        $new_value[] = (string) $item;
      }
    }

    // We return an array of [0 => null] so that the extract plugin won't fail.
    return $new_value ?: [NULL];
  }

}
