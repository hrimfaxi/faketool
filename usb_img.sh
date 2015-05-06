#!/bin/sh

FAKE_ROOT=/home/hrimfaxi/.fake/

date >> $FAKE_ROOT/usb.log
UUID=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1)
echo dd if=$1 of=$FAKE_ROOT/$(basename $1)-$UUID bs=32M >> $FAKE_ROOT/usb.log
dd if=$1 of=$FAKE_ROOT/$(basename $1)-$UUID bs=32M
