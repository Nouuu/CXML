#!/bin/bash

if [ "$(id -u)" != "0" ]; then
  echo "You must start this script with root privileges"
  exit 1
fi

exe_path=part_1/linux
exe_name=CXML_1_V2.0
part=1
version=2.0
readonly user=$SUDO_USER

echo "Hello $user"
echo "Installing CXML part $part version $version"
echo "Creating install folder"
sudo mkdir -p /opt/cxml/

echo "Copying executable"
sudo cp -rf $exe_path/$exe_name /opt/cxml/cxml_$part

echo "Ajusting executable rights"

sudo chmod -R +x /opt/cxml

echo "Create path executable alias"
echo "alias cxml_$part='/opt/cxml/cxml_$part'" >>/home/$user/.bashrc

echo "Refresh environment alias"

# shellcheck disable=SC1090
source /home/$user/.bashrc

echo "Program successfully installed !"
echo "Execute this command to finalize installation : 'source ~/.bashrc'"
echo "After that, simply run 'cxml_$part' to run it"

exit 0
