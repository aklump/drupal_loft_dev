#!/usr/bin/env bash
sass=./node_modules/.bin/sass

test -e "dist" && rm -r "dist"
$sass --style=compressed "scss/loft_dev.scss" "dist/loft_dev.css"
