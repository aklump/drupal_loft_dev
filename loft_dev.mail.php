<?php
// $Id: loft_dev.mail.php 155 2010-06-07 14:13:14Z aklump $

/**
 * @file
 * This file simply tests the server's mail function
 */
$to = 'aaron@intheloftstudios.com';
$from = 'booking@djskout.com';

if (mail($to, 'testing server email', 'does the server send email?', 'from: '. $from)) {
  print 'The server has sent an email to '. $to;
}
else {
  print 'The server COULD NOT SEND an email to '. $to;
}