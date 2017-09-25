#!/usr/bin/expect

set timeout -1
spawn ssh -p 10022 root@bd3
expect "*password:" { send "1qa@WS\r" }
interact
