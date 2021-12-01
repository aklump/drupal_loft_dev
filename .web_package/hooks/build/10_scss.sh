#!/usr/bin/env bash
# https://www.npmjs.com/package/node-sass-chokidar
sass=./node_modules/.bin/node-sass-chokidar

# config
style=compressed
# endconfig

test -e "$7/dist" && rm -r "$7/dist"
$sass --output-style=${style} "$7/scss/loft_dev.scss" -o "$7/dist"
