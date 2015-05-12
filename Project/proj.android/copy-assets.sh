#!/bin/sh

#  copy-assets.sh
#  
#
#  Created by v.boichuk on 1/10/14.
#

SCRIPT_DIR=$(dirname "$0")
RESOURCES_DIR=$SCRIPT_DIR/../Resources
ASSETS_DIR=$SCRIPT_DIR/assets

echo "clear"

if [ -d $TMP_DIR ]; then
    rm -rf $TMP_DIR
fi
mkdir -p $TMP_DIR

if [ -d $ASSETS_DIR ]; then
rm -rf $ASSETS_DIR
fi
mkdir -p $ASSETS_DIR

if [ -f $ZIPFILE ]; then
rm -f $ZIPFILE
fi

echo "copy files"

rsync -a \
--exclude='.?*' \
$RESOURCES_DIR/ $ASSETS_DIR