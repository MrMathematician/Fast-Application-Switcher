#!/bin/bash

sudo -v

cmake CMakeLists.txt
make

sudo cp FastApplicationSwitcher /usr/local/bin/

read -p "Enter your username: " name

touch /home/$name/.config/systemd/user/fastapplicationswitcher.service

sudo bash -c 'cat > /etc/systemd/system/fastapplicationswitcher.service <<EOF

[Unit]
Description=Fast Application Switcher

[Service]
Type=simple
ExecStart=/usr/local/bin/FastApplicationSwitcher
Restart=on-failure
Environment=DISPLAY=:0
Environment=XAUTHORITY=/home/$USER/.Xauthority
EOF
'



sudo systemctl daemon-reload
sudo systemctl start fastapplicationswitcher
