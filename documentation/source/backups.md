# Automatic Backups Using Loft Deploy

Loft Dev Module can automatically call `loft_deploy export` on regular intervals of use.  [Loft Deploy](https://github.com/aklump/loft_deploy) must already be installed and configured for your project.  This has the effect of automatically backing up the database to the normal _Loft Deploy_ output path, for every N minutes of **active** use.

    .
    ├── my_db_name-auto_2019-05-05_1906.sql.gz
    ├── my_db_name-auto_2019-05-05_1901.sql.gz
    └── my_db_name-auto_2019-05-05_1856.sql.gz

This is not based on cron, but rather on elapsed time.  If you set this to back up every 15 minutes, it will only do so if you're activaly using the site.  It's like poor man's cron, it looks to see if N minutes has elapsed since the last backup, and it does this on a page load.  Thus, no use, no page load.  The following settings needed to be added to _settings.local.php_.

`loft_deploy purge` is also called based on `$config['loft_dev.settings']['loft_deploy_purge_after_days']`, which will keep your total file count down.

## Configuration

    $config['loft_dev.settings']['which_loft_deploy'] = '/Users/aklump/bin/loft_deploy';
    $config['loft_dev.settings']['loft_deploy_export_period_mins'] = 5;
    $config['loft_dev.settings']['loft_deploy_purge_after_days'] = 3;

To disable simply comment out the above lines.    
