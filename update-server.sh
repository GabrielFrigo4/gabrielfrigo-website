#!/bin/sh
scp -r -i "$HOME/.key/ssh-key-frigo-server.key" "$1" "ubuntu@144.22.210.65:/home/ubuntu/$1"
