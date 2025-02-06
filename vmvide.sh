#!/bin/bash
echo "penser a enlever la vm apres "
multipass launch --cloud-init ./cloud-config.yaml --name test --cpus 10  --memory 8G
multipass shell test