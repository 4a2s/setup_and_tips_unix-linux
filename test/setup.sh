#!/bin/bash
sudo apt update
sudo snap install multipass
echo "penser a enlever la vm apres "
multipass launch --cloud-init ./cloud-config.yaml --name test
multipass shell test


