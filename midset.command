#!/bin/bash
echo See README.txt for help if needed
echo -n "Drag and drop the file that contains your dots here: "
read file
echo running midset $file ...
echo
~/Desktop/midset/midset $file
echo
echo -n Press ENTER when done.
read
