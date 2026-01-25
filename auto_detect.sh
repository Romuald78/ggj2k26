#!/bin/bash

# check for keyboard
keyboard=$(ls /dev/input/by-path | grep 'event-kbd')

# check for mouse
mouse=$(ls /dev/input/by-path | grep 'event-mouse')

# store links in config
mkdir -p config
echo  "KEYBOARD;/dev/input/by-path/$keyboard" >  'config/events.cfg'
echo  "MOUSE;/dev/input/by-path/$mouse"    >> 'config/events.cfg'
chown -R cytech:cytech 'config/'

