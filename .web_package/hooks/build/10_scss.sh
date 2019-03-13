#!/usr/bin/env bash
bump_sass=$(type sass >/dev/null &2>&1 && which sass)

[[ -d "dist/" ]] || mkdir "dist/"
$bump_sass  --style=compressed --no-cache --update "$7/scss/loft_dev.scss:$7/dist/loft_dev.css"
