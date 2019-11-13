#!/bin/bash
echo "j'applique le salt"
salt-call state.apply
../../executable/in_test tun0 VM1-6
