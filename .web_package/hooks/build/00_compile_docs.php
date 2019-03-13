<?php

/**
 * @file
 * Generates documentation, adjusts paths and adds to SCM.
 */

namespace AKlump\WebPackage;

$build
  ->setDocumentationSource('documentation')
  ->generateDocumentationTo('docs')
  // Add some additional files to SCM that were generated and outside of the docs directory.
  ->addFilesToScm([
    'README.md',
    'README.txt',
    'CHANGELOG.md',
  ])
  ->displayMessages();
