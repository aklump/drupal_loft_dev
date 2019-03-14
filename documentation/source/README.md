# Drupal Module: Loft Dev
**Author:** Aaron Klump  <sourcecode@intheloftstudios.com>

##Summary
**Provides a suite of development tools for Drupal.**

## Features

* Alerts you when the [reroute email module]() is not properly configured.
* Adds the ability to sandbox code using _sandbox.inc_ and `?sb`
* Adds new Twig function `file_header()` to generate template headers.
* Adds demo page for _Page Not Found_
* Adds demo page for _Access Denied_

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

### Load a view mode with all fields hidden, weights & labels reset
> In order to make this work you will first have to disable any Display Suite layout that is chosen for the view mode!

Append `?reset`to the url of the view mode edit page and refresh

These options available are:

| query param | desctiption |
|----------|----------|
| &label= | above|inline|hidden |

Example usage:

    admin/structure/types/manage/video/display/teaser?reset&label=hidden

### Troubleshooting mail issues

If you set the variable _loft_dev_mail_capture_ to 1, emails will be written to _private://loft-dev/mail_ and you can see the emails that are being sent.  They will not be actually sent while this is true.  See `loft_dev_mail_alter()` and `loft_dev_exit()` for more info.

### Database Schema Rollbacks

You can easily rollback the module version using the loft dev tools block "Replay Update" button.  By default the schema will be rolled back by one number.  You can also target a specific rollback number by setting the following variable to the schema version you want to rollback to:

    drush vset loft_dev:update_rollback_{module name} {schema version, e.g. 7004}


## Integration with drupal_deploy

Add the somthing like the following to your settings file so the current deploy folder can be located:

    $conf['loft_dev_drupal_deploy_path'] = realpath(DRUPAL_ROOT . '/../drupal_deploy/user/deploy_2.0');
    
## Theme Playground Templates (on `?pg` or off `?pg=0`)

For rapid development, a feature exists called the theme playground where you can swap out flat file versions of your tpl files.  This is good when your content is not ready, or you just want to try out a different version of a tpl file.

1. In your active theme, create tpl variations following this pattern `{theme}--loft-dev-playground.tpl.php`, e.g., `html--loft-dev-playground.tpl.php`.
1. Clear cache each time you add or rename a tpl file.
1. Activate these templates by either visiting the playground url `/loft-dev/theme/playground`or by appending `?pg` to the query string at any path.  When activated, these template files will be used instead of the normal ones.

##Contact
* **In the Loft Studios**
* Aaron Klump - Developer
* PO Box 29294 Bellingham, WA 98228-1294
* _aim_: theloft101
* _skype_: intheloftstudios
* _d.o_: aklump
* <http://www.InTheLoftStudios.com>
