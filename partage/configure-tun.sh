#!/bin/bash
echo "j'applique le salt"
salt-call state.apply
sleep 10s
make tunalloc
sleep 3s
./tunalloc tun0
sleep 3s

ip link set tun0 up
sleep 1s
ip addr add 172.16.2.1/24 dev tun0

# sudo ip addr add 172.16.2.180/24 dev tun0
# pour VM1-6 pour rediriger correctement paquet vers tun0
