# Drupal Module: Loft Dev
**Author:** Aaron Klump  <sourcecode@intheloftstudios.com>

##Summary
**Provides a suite of development tools for Drupal.**

##Requirements

##Installation
1. Install as usual, see [http://drupal.org/node/70151](http://drupal.org/node/70151) for further information.

##Configuration
2. You most likely want to add the following line to _settings.local.php_.  This will insure that the **dev tools appear on every page, for every role, regardless of permissions**.  The alternative is to setup roles for the permission _loft_dev:use tools_.

        $conf['loft_dev_free_access'] = TRUE;

### Hide Admin Stuff
1. Hold down the meta key when clicking Hide Admin Stuff for a 3 minute hide.
1. Extend the admin stuff selectors using `hook_loft_dev_admin_stuff()`.

## Automatic backups using Loft Deploy
Loft Dev module can automatically call `loft_deploy export` on regulary intervals of use.  This has the effect of automatically backing up the database to the normal output path, for every N minutes of active use.  For the most recent backup go there.  To see the incremental backups in time, descend into the _loft_dev_auto_ directory.

This is not based on cron, but rather on elapsed time.  If you set this to back up every 15 minutes, it will only do so if you're activaly using the site.  It's like poor man's cron, it looks to see if N minutes has elapsed since the last backup, and it does this on a page load.  Thus, no use, no page load.  The following settings needed to be added to _settings.local.php_.

To disable this feature set it to 0.
        
        $conf['loft_dev_which_ld'] = '/Volumes/Data/Users/aklump/bin/loft_deploy';
        $conf['loft_dev_loft_deploy_export_period_mins'] = 5;

You may also need to add the following to .loft_deploy/config

        ld_mysqldump='/Applications/MAMP/Library/bin/mysqldump'
        ld_gzip='/usr/bin/gzip'        
    


##Contact
* **In the Loft Studios**
* Aaron Klump - Developer
* PO Box 29294 Bellingham, WA 98228-1294
* _aim_: theloft101
* _skype_: intheloftstudios
* _d.o_: aklump
* <http://www.InTheLoftStudios.com>