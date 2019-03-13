<?php

/**
 * @file
 * PHP mail() test script.
 *
 * This file simply tests the server's mail function.  It is standalone and
 *   doesn't use a Drupal bootstrap.  Copy it to a server whose mail ability is
 *   in question.
 */

$to = 'email@site.com';
$from = 'email@site.com';

$headers = array();
$headers[] = 'From: ' . $from;
$message = 'Does this server send email?';
$success = mail($to, 'Testing server email', $message, implode("\r\n", $headers));
if ($success) {
  print 'The server has sent an email to ' . $to;
}
else {
  print 'The server COULD NOT SEND an email to ' . $to;
}
exit;
