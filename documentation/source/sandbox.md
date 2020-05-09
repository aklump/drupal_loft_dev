# Sandbox (on `?sb` or off `?sb=0`)

Sandbox mode is activated by appending to the query string.  What you append, depends upon what you've provided in the hook callback.  When you active this mode, the file that is provided in the hook will be called after a full bootstrap; use it to test code without having to change paths.

## Theme

To change the active theme used by the sandbox file, enter the name of the theme in the query string, e.g. 

    ?sb=1&theme=gop_theme
