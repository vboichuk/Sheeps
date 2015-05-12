#!/bin/bash

SCRIPT_DIR=$(dirname "$0")
PROJECT_DIR=$SCRIPT_DIR/..

cd $PROJECT_DIR

CURRENT_DATE=`date +%Y.%m.%d`
CURRENT_TIME=`date +%H-%M`

ARCHIVE_NAME=~/"Sheeps_(${CURRENT_DATE})_(${CURRENT_TIME}).zip"

echo $ARCHIVE_NAME

zip -0 -r $ARCHIVE_NAME * \
--exclude "*.DS_Store" \
--exclude "*.class" \
--exclude "*.obj"
