#!/usr/bin/expect

################################################################################
# This script is used to run the application on the QNX target.
# This is done in the following steps:
# 1) Transfer the application binary to the QNX target
# 2) Use telnet to connect and make the application executable
################################################################################

set timeout 5

set host 192.168.1.212
set port 23
set ftpLogin qnxuser
set ftpPassword qnxuser
set telnetLogin root
set telnetPassword root

################################################################################
# Upload the file via FTP to the QNX node.
################################################################################
spawn ftp ftp://$ftpLogin:$ftpPassword@$host

send "cd tmp\r"
expect "ftp>"

send "put build/aarch64le-debug/QNX_EdgeSys_Base MATERIAL/RPI_BBW_distributed\r"
expect "ftp>"

send "mkdir QNX_DSE/output\r"
expect "ftp>"

send "bye\r"
expect EOF
wait -nowait

################################################################################
# Connect via Telnet, make the file executable and run the application.
################################################################################
spawn telnet $host $port

expect "login: "
send "$telnetLogin\r"

expect "password: "
send "$telnetPassword\r"
expect "#"

send "cd /tmp/MATERIAL\r"
expect "#"

send "chmod +x RPI_BBW_distributed\r"
expect "#"


send "exit\r"
expect EOF
wait
