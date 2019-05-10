#!/bin/expect
set timeout 30
spawn scp ./shadowsocks.sh root@159.138.57.58:/root/
expect {
    -nocase -re "password:" {
      send "Huawei123\n"
    }
    -nocase -re "yes/no" {
      send "yes\n"
      expect "password:"
      send "Huawei123\n"
    }
}

spawn ssh -l root 159.138.57.58 "sh /root/shadowsocks.sh"
expect {
    -nocase -re "password:" {
      send "Huawei123\n"
    }
    -nocase -re "yes/no" {
      send "yes\n"
      expect "password:"
      send "Huawei123\n"
    }
}
