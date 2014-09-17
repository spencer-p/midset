#!/bin/bash
echo -n Type the path of the file that contains your dots: 
read $file
echo running midset $file ...
echo
~/Desktop/midset/midset $file
