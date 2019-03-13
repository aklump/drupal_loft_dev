# Image Styles

## Automatic Image Style Flush During Development

When developing image styles it can be a pane to flush them, here is a script that you can use to erase all derivatives every _period_ seconds.  

1. Copy  _loft_dev/bin/style_flusher.sh_ to _public://files/style_flusher.sh_ 
2. Make sure the file is executable: 
   
        $ cd {path to files} & chmod 700 style_flusher.sh

4. Start the watcher to delete hero styles...
        
        $ ./style_flusher.sh hero

4. Add a second argument to alter the period of deletion to 5 seconds.
        
        $ ./style_flusher.sh hero 5

5. Press _CTRL-c_ to stop the watcher.

### Gotcha!

1. Make sure you have the browser dev tools open with caching turned off to remove the layer of browser image caching.
