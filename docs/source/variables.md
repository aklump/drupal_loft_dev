# Hardcoded data/variables

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
