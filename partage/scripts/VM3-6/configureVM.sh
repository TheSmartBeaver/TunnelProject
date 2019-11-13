#!/bin/bash
echo "j'applique le salt"
salt-call state.apply
../../executable/out_test tun0 VM3-6
