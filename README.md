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

##Suggested Use

## Design Decisions/Rationale

##Contact
* **In the Loft Studios**
* Aaron Klump - Developer
* PO Box 29294 Bellingham, WA 98228-1294
* _aim_: theloft101
* _skype_: intheloftstudios
* _d.o_: aklump
* <http://www.InTheLoftStudios.com>