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

## Usage

### Troubleshooting mail issues
If you set the variable _loft_dev_mail_capture_ to 1, emails will be written to _private://loft-dev/mail_ and you can see the emails that are being sent.  They will not be actually sent while this is true.  See `loft_dev_mail_alter()` and `loft_dev_exit()` for more info.

### Database Schema Rollbacks
You can easily rollback the module version using the loft dev tools block "Replay Update" button.  By default the schema will be rolled back by one number.  You can also target a specific rollback number by setting the following variable to the schema version you want to rollback to:

    drush vset loft_dev:update_rollback_{module name} {schema version, e.g. 7004}

### Automatic backups using Loft Deploy
Loft Dev module can automatically call `loft_deploy export` on regulary intervals of use.  This has the effect of automatically backing up the database to the normal output path, for every N minutes of active use.  For the most recent backup go there.  To see the incremental backups in time, descend into the _loft_dev_auto_ directory.

This is not based on cron, but rather on elapsed time.  If you set this to back up every 15 minutes, it will only do so if you're activaly using the site.  It's like poor man's cron, it looks to see if N minutes has elapsed since the last backup, and it does this on a page load.  Thus, no use, no page load.  The following settings needed to be added to _settings.local.php_.

To disable this feature set it to 0.
        
    $conf['loft_dev_which_ld'] = '/Volumes/Data/Users/aklump/bin/loft_deploy';
    $conf['loft_dev_loft_deploy_export_period_mins'] = 5;

You may also need to add the following to .loft_deploy/config

    ld_mysqldump='/Applications/MAMP/Library/bin/mysqldump'
    ld_gzip='/usr/bin/gzip'        

## Integration with drupal_deploy
Add the somthing like the following to your settings file so the current deploy folder can be located:

    $conf['loft_dev_drupal_deploy_path'] = realpath(DRUPAL_ROOT . '/../drupal_deploy/user/deploy_2.0');

## Sandbox (on `?sb` or off `?sb=0`)
Sandbox mode is activated by appending to the query string.  What you append, depends upon what you've provided in the hook callback.  When you active this mode, the file that is provided in the hook will be called after a full bootstrap; use it to test code without having to change paths.
    
## Theme Playground Templates (on `?pg` or off `?pg=0`)

For rapid development, a feature exists called the theme playground where you can swap out flat file versions of your tpl files.  This is good when your content is not ready, or you just want to try out a different version of a tpl file.

1. In your active theme, create tpl variations following this pattern `{theme}--loft-dev-playground.tpl.php`, e.g., `html--loft-dev-playground.tpl.php`.

1. Activate these templates by either visiting the playground url `/loft-dev/theme/playground`or by appending `?pg` to the query string at any path.  When activated, these template files will be used instead of the normal ones.


## Hardcoded data/variables
Normally template variables are provided by the database and other functions.  You can hardcode variable values for your templates using files in a folder called `loft_dev_playground`.

1. In your active theme, create a folder called loft_dev_playground.
1. In this folder place files that contain values, e.g. `page.content.php`.  The filename is important as it maps to a php array like this:

    page.content.php -> $page['content']
    page.foo.bar.baz.php -> $page['foo']['bar']['baz']
        
1. The value of the variable is whatever is printed by that file, e.g. 

    <?php
    /**
     * @file
     * Provides a hardcoded variable for $page['content']
     *
     * This file is named page.content.php
     */
    ?>
    <p>This is the value of the variable</p>

1. Or it could also be something like this:

    <?php
    /**
     * @file
     * Provides a hardcoded variable for $page['content']
     *
     * This file is named page.content.php
     */
    $build['item_list'] = array(
      '#theme' => 'item_list',
      '#items' => array('do', 're', 'mi'),
      '#type' => 'ol',
    );
    print render($build);


1. Append `?ldp_data` to any url to load content from the theme directory `loft_dev_playground`.  Alternately, you may set a system var and content will be pulled always, so long as the file contains something; set this var:

    $conf['loft_dev_playground_load_data'] = TRUE;

* You can also disable by adding `ldp_data=0` to the url.
* See `hook_loft_dev_playground_info`.

1. You can ignore certain files without having to delete them by using a file `loft_dev_playground/config.json`, e.g.: 

    {
        "ignore": [
            "page.content.php"
        ]
    }

##Contact
* **In the Loft Studios**
* Aaron Klump - Developer
* PO Box 29294 Bellingham, WA 98228-1294
* _aim_: theloft101
* _skype_: intheloftstudios
* _d.o_: aklump
* <http://www.InTheLoftStudios.com>