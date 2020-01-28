#!/bin/bash
apt-get remove libreoffice-common
apt-get remove unity-webapps-common
apt-get remove thunderbird totem rhythmbox empathy brasero simple-scan gnome-mahjongg aisleriot gnome-mines cheese transmission-common gnome-orca webbrowser-app gnome-sudoku  landscape-client-ui-install
apt-get remove onboard deja-dup
apt-get remove gnome-software gnome-todo gedit gnome-power-manager update-manager update-manager-common update-nitifier update-notifier-common 
apt-get autoremove
