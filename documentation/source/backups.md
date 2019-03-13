# Automatic backups using Loft Deploy

Loft Dev module can automatically call `loft_deploy export` on regulary intervals of use.  This has the effect of automatically backing up the database to the normal output path, for every N minutes of active use.  For the most recent backup go to: _{$local_db_dir}/loft_dev_auto.sql.gz_. For those before that look inside: _{$local_db_dir}/loft_dev_auto/_.

    .
    ├── intheloftstudios_loft-loft_dev_auto.sql.gz
    └── loft_dev_auto
        └── 2018-01-12_1313_intheloftstudios_loft-loft_dev_auto.sql.gz

This is not based on cron, but rather on elapsed time.  If you set this to back up every 15 minutes, it will only do so if you're activaly using the site.  It's like poor man's cron, it looks to see if N minutes has elapsed since the last backup, and it does this on a page load.  Thus, no use, no page load.  The following settings needed to be added to _settings.local.php_.

## Configuration

    $conf['loft_dev_which_ld'] = '/Users/aklump/bin/loft_deploy';
    $conf['loft_dev_loft_deploy_export_period_mins'] = 5;
    
To disable, set to 0:

    $conf['loft_dev_loft_deploy_export_period_mins'] = 0

You may also need to add the following to _.loft_deploy/config_

    ld_mysqldump='/Applications/MAMP/Library/bin/mysqldump'
    ld_gzip='/usr/bin/gzip'        
