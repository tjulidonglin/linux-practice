#!/bin/bash
apt remove -y libreoffice-common
apt remove -y unity-webapps-common
apt remove -y thunderbird totem rhythmbox empathy brasero simple-scan gnome-mahjongg aisleriot gnome-mines cheese transmission-common gnome-orca webbrowser-app gnome-sudoku  landscape-client-ui-install
apt remove -y onboard deja-dup
apt remove -y gnome-software gnome-todo gedit gnome-power-manager update-manager update-manager-common update-nitifier update-notifier-common 
apt remove -y gnome-software
apt remove -y update-manager
apt remove -y software-properties-gtk
apt remove -y gedit
apt remove -y firefox
apt autoremove -y
