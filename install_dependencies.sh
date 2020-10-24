#!/bin/bash

# This script installs all the dependencies required for CXML
#
# It installs the following packages:
#   - libgtk-3-dev          --> GTK3 SDK

if [ "$(id -u)" != "0" ]; then
  echo "You must start this script with root privileges"
  exit 1
fi

apt-get -y install \
  gcc \
  make \
  libgtk-3-dev \
  cmake
