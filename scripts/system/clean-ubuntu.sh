#!/bin/bash
apt-get remove -y libreoffice-common
apt-get remove -y unity-webapps-common
apt-get remove -y thunderbird totem rhythmbox empathy brasero simple-scan gnome-mahjongg aisleriot gnome-mines cheese transmission-common gnome-orca webbrowser-app gnome-sudoku  landscape-client-ui-install
apt-get remove -y onboard deja-dup
apt-get remove -y gnome-software gnome-todo gedit gnome-power-manager update-manager update-manager-common update-nitifier update-notifier-common 
apt-get remove -y gnome-software software-center
apt-get remove -y update-manager-core
apt-get remove -y ubuntuone-client
apt-get remove -y update-manager
apt-get remove -y software-properties-gtk
apt-get remove -y gedit
apt-get remove -y firefox
apt-get autoremove -y
