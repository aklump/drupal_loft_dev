#!/usr/bin/env php
<?php

/**
 * @file
 * Replace all existing file headers with {{ file_header() }}.
 *
 * @code
 *   ./remove_twig_headers.php /path/to/template/dir
 * @endcode
 *
 * You may visit: http://globalonenessproject.local.loft/design-guide/view to
 * load all components at once, which will process the functions, and update the
 * headers wit the new values.
 */

$base_directory = $argv[1];

$directory = new RecursiveDirectoryIterator($base_directory);
$iterator = new RecursiveIteratorIterator($directory);
$twig_files = new RegexIterator($iterator, '/^.+\.html.twig$/i', RecursiveRegexIterator::GET_MATCH);

foreach ($twig_files as $set) {
  $twig_filepath = $set[0];
  $contents = file_get_contents($twig_filepath);
  $before = $contents;
  $contents = preg_replace('/\{\#\s*\/\*\*\s*\*\s*@file.+?\*\/\s*\#\}\s*/s', "{{ file_header() }}\n", $contents);
  if ($before !== $contents) {
    echo str_replace(__DIR__, '', $twig_filepath) . PHP_EOL;
    file_put_contents($twig_filepath, $contents);
  }
}

echo "Done." . PHP_EOL . PHP_EOL;


