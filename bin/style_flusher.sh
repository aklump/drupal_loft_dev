#!/usr/bin/env bash
#
# Sets up a watcher to delete image style derivatives of $1 every $2 seconds.
#
# 1. Copy this file to public://files
# 2. chmod 700
# 3. call it to watch and delete styles when developing new styles.
#
if [ ! "$1" ]; then
    echo 'Call with a style name as your argument'
    exit
fi

# Get the actual directory of the script, making sure it's in files
source="${BASH_SOURCE[0]}"
dir="$( cd -P "$( dirname "$source" )" && pwd )"
dir="$(basename "${dir}")"
if [ "$dir" != "files" ]; then
    echo "This script is expecting to be located in a directory called 'files'"
    exit
fi

style=styles/$1
period=3
if [ $# -gt 1 ]; then
    period=$2
fi

# Start the watcher
echo "Deleting $style derivatives every $period seconds... Press CTRL-c to stop."
while true; do
    sleep $period
    test -e "$style" && find "$style" -type f -exec rm -v {} \;
done
