#!/bin/bash
gcc -o libxml ../app.cpp -I/usr/include/libxml2 -L/usr/lib -lxml2
