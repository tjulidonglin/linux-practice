#!/bin/bash
apt update
apt install -y python-pip
pip install shadowsocks

cat > /etc/shadowsocks.json <<EOF
{
	"server":"0.0.0.0",
	"server_port":443,
	"local_port":1080,
	"password":"Huawei123",
	"timeout":600,
	"method":"aes-256-cfb"
}
EOF
ssserver -c /etc/shadowsocks.json -d start&
