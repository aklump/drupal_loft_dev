var tipuesearch = {"pages":[{"title":"Drupal Module: Loft Dev","text":"  Author: Aaron Klump  &#x73;&#111;&#117;&#x72;&#x63;&#101;c&#x6f;&#100;&#101;&#x40;&#x69;&#110;&#116;&#x68;&#x65;&#108;&#x6f;&#x66;&#116;&#115;&#x74;&#x75;&#100;i&#x6f;&#115;&#46;&#x63;&#x6f;&#109;  Summary  Provides a suite of development tools for Drupal.  Requirements  Installation   Install as usual, see http:\/\/drupal.org\/node\/70151 for further information.   Configuration   You most likely want to add the following line to settings.local.php.  This will insure that the dev tools appear on every page, for every role, regardless of permissions.  The alternative is to setup roles for the permission loft_dev:use tools.  $conf['loft_dev_free_access'] = TRUE;   Hide Admin Stuff   Hold down the meta key when clicking Hide Admin Stuff for a 3 minute hide. Extend the admin stuff selectors using hook_loft_dev_admin_stuff().   Usage  Load a view mode with all fields hidden, weights &amp; labels reset     In order to make this work you will first have to disable any Display Suite layout that is chosen for the view mode!   Append ?resetto the url of the view mode edit page and refresh  These options available are:       query param   desctiption       &amp;label=   above|inline|hidden     Example usage:  admin\/structure\/types\/manage\/video\/display\/teaser?reset&amp;label=hidden   Troubleshooting mail issues  If you set the variable loft_dev_mail_capture to 1, emails will be written to private:\/\/loft-dev\/mail and you can see the emails that are being sent.  They will not be actually sent while this is true.  See loft_dev_mail_alter() and loft_dev_exit() for more info.  Database Schema Rollbacks  You can easily rollback the module version using the loft dev tools block \"Replay Update\" button.  By default the schema will be rolled back by one number.  You can also target a specific rollback number by setting the following variable to the schema version you want to rollback to:  drush vset loft_dev:update_rollback_{module name} {schema version, e.g. 7004}   Integration with drupal_deploy  Add the somthing like the following to your settings file so the current deploy folder can be located:  $conf['loft_dev_drupal_deploy_path'] = realpath(DRUPAL_ROOT . '\/..\/drupal_deploy\/user\/deploy_2.0');   Theme Playground Templates (on ?pg or off ?pg=0)  For rapid development, a feature exists called the theme playground where you can swap out flat file versions of your tpl files.  This is good when your content is not ready, or you just want to try out a different version of a tpl file.   In your active theme, create tpl variations following this pattern {theme}--loft-dev-playground.tpl.php, e.g., html--loft-dev-playground.tpl.php. Clear cache each time you add or rename a tpl file. Activate these templates by either visiting the playground url \/loft-dev\/theme\/playgroundor by appending ?pg to the query string at any path.  When activated, these template files will be used instead of the normal ones.   Contact   In the Loft Studios Aaron Klump - Developer PO Box 29294 Bellingham, WA 98228-1294 aim: theloft101 skype: intheloftstudios d.o: aklump http:\/\/www.InTheLoftStudios.com  ","tags":"","url":"README.html"},{"title":"Tasklist","text":"    ","tags":"","url":"_tasklist.html"},{"title":"Automatic backups using Loft Deploy","text":"  Loft Dev module can automatically call loft_deploy export on regulary intervals of use.  This has the effect of automatically backing up the database to the normal output path, for every N minutes of active use.  For the most recent backup go to: {$local_db_dir}\/loft_dev_auto.sql.gz. For those before that look inside: {$local_db_dir}\/loft_dev_auto\/.  . \u251c\u2500\u2500 intheloftstudios_loft-loft_dev_auto.sql.gz \u2514\u2500\u2500 loft_dev_auto     \u2514\u2500\u2500 2018-01-12_1313_intheloftstudios_loft-loft_dev_auto.sql.gz   This is not based on cron, but rather on elapsed time.  If you set this to back up every 15 minutes, it will only do so if you're activaly using the site.  It's like poor man's cron, it looks to see if N minutes has elapsed since the last backup, and it does this on a page load.  Thus, no use, no page load.  The following settings needed to be added to settings.local.php.  Configuration  $conf['loft_dev_which_ld'] = '\/Users\/aklump\/bin\/loft_deploy'; $conf['loft_dev_loft_deploy_export_period_mins'] = 5;   To disable, set to 0:  $conf['loft_dev_loft_deploy_export_period_mins'] = 0   You may also need to add the following to .loft_deploy\/config  ld_mysqldump='\/Applications\/MAMP\/Library\/bin\/mysqldump' ld_gzip='\/usr\/bin\/gzip'          ","tags":"","url":"backups.html"},{"title":"Drupal Block","text":"  To see the checklist in drupal, assign the block to a valid region.  Configuration XML  A private file needs to be created at: private::loft_dev\/page_review\/checklist.xml using the following pattern.  &lt;config&gt;   &lt;status value=\"0\"&gt;not started&lt;\/status&gt;   &lt;status value=\"1\"&gt;done&lt;\/status&gt;   &lt;page\/&gt;   &lt;page\/&gt; &lt;\/config&gt;     Each XML &lt;status\/&gt; defines a status code\/name  Define the status values in the xml, which are then used in the page nodes.  Each XML &lt;page\/&gt; consists of  &lt;page weight=\"12\"&gt;   &lt;status&gt;1&lt;\/status&gt;   &lt;title&gt;Theme&lt;\/title&gt;   &lt;comp&gt;https:\/\/www.globalonenessproject.org\/node\/3139&lt;\/comp&gt;   &lt;notes&gt;{uri}&lt;\/notes&gt;   &lt;guide&gt;{uri}&lt;\/guide&gt;   &lt;uri&gt;node\/3139&lt;\/uri&gt; &lt;\/page&gt;        attribute   description   example       weight   The sort order   3          child   description   example       status   The pages development status   1     title   A description for the page   User signup     uri*   url to the drupal page   {url}     guide*   url to pattern lab guide   {url}     comp*   url to a comp   {url}     notes*   url to notes   {url}      allows multiple nodes.   Status values       status   meaning       0   in dev     1   done     2   prototype in process     3   prototype finished     4   minor css needed    ","tags":"","url":"checklist.html"},{"title":"Image Styles","text":"  Automatic Image Style Flush During Development  When developing image styles it can be a pane to flush them, here is a script that you can use to erase all derivatives every period seconds.   Copy  loft_dev\/bin\/style_flusher.sh to public:\/\/files\/style_flusher.sh Make sure the file is executable:  $ cd {path to files} &amp; chmod 700 style_flusher.sh  Start the watcher to delete hero styles...  $ .\/style_flusher.sh hero  Add a second argument to alter the period of deletion to 5 seconds.  $ .\/style_flusher.sh hero 5  Press CTRL-c to stop the watcher.   Gotcha!   Make sure you have the browser dev tools open with caching turned off to remove the layer of browser image caching.  ","tags":"","url":"image_styles.html"},{"title":"Page Review","text":"  @todo ","tags":"","url":"page_review.html"},{"title":"Sandbox (on <code>?sb<\/code> or off <code>?sb=0<\/code>)","text":"  Sandbox mode is activated by appending to the query string.  What you append, depends upon what you've provided in the hook callback.  When you active this mode, the file that is provided in the hook will be called after a full bootstrap; use it to test code without having to change paths. ","tags":"","url":"sandbox.html"},{"title":"Search Results","text":" ","tags":"","url":"search--results.html"},{"title":"Twiggy Module Support (Twig)","text":"   Adds support for auto-generated headers of twig templates. Create your twig template. Add the following to the top of the file:  {{ file_header() }}  Reload the page that renders the file. You twig template file should now contain a header of the available variables. Remove {{ file_header() }} from your twig file.  ","tags":"","url":"twiggy.html"},{"title":"Hardcoded data\/variables","text":"  Normally template variables are provided by the database and other functions.  You can hardcode variable values for your templates using files in a folder called loft_dev_playground.   In your active theme, create a folder called loft_dev_playground. In this folder place files that contain values, e.g. page.content.php.  The filename is important as it maps to a php array like this:  page.content.php -&gt; $page['content'] page.foo.bar.baz.php -&gt; $page['foo']['bar']['baz']  The value of the variable is whatever is printed by that file, e.g.  &lt;?php \/**  * @file  * Provides a hardcoded variable for $page['content']  *  * This file is named page.content.php  *\/ ?&gt; &lt;p&gt;This is the value of the variable&lt;\/p&gt;  Or it could also be something like this:  &lt;?php \/**  * @file  * Provides a hardcoded variable for $page['content']  *  * This file is named page.content.php  *\/ $build['item_list'] = array(   '#theme' =&gt; 'item_list',   '#items' =&gt; array('do', 're', 'mi'),   '#type' =&gt; 'ol', ); print render($build);  Append ?ldp_data to any url to load content from the theme directory loft_dev_playground.  Alternately, you may set a system var and content will be pulled always, so long as the file contains something; set this var:  $conf['loft_dev_playground_load_data'] = TRUE;     You can also disable by adding ldp_data=0 to the url. See hook_loft_dev_playground_info.    You can ignore certain files without having to delete them by using a file loft_dev_playground\/config.json, e.g.:  {     \"ignore\": [         \"page.content.php\"     ] }   ","tags":"","url":"variables.html"}]};
