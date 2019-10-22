#!/bin/bash
gcc tunalloc.c -o tunalloc
sleep 1s
./tunalloc tun0 &
sleep 1s
ip addr add 172.16.2.1/28 dev tun0
