#!/bin/Zsh

# This script compiles the QNX_DSE project from scratch without the need to
# open the IDE.

# Set all variables needed for compilation
AS="qcc -V8.3.0,gcc_ntoaarch64le"
BUILD_PROFILE="debug"
CC="qcc -V8.3.0,gcc_ntoaarch64le"
CPUVARDIR="aarch64le"
CWD="/Users/mabecker/ide-7.1-workspace"
CXX="q++ -V8.3.0,gcc_ntoaarch64le_cxx"
DYLD_LIBRARY_PATH="/Users/mabecker/qnx710/host/darwin/x86_64/usr/lib:/Users/mabecker/qnx710/host/darwin/x86_64/lib:/Users/mabecker/qnx710/host/darwin/x86_64/lib/dll:"
LD="qcc -V8.3.0,gcc_ntoaarch64le"
MAKEFLAGS="-I/Users/mabecker/qnx710/target/qnx7/usr/include"
PATH="/Users/mabecker/qnx710/host/darwin/x86_64/usr/bin:/Users/mabecker/qnx710/host/darwin/x86_64/bin:/Users/mabecker/qnx710/host/darwin/x86_64/usr/sbin:/Users/mabecker/qnx710/host/darwin/x86_64/sbin:/Users/mabecker/qnx710/host/common/bin::/usr/bin:/bin:/usr/sbin:/sbin"
PLATFORM="aarch64le"
PWD="/Users/mabecker/ide-7.1-workspace"
PYTHONDONTWRITEBYTECODE="1"
QCC_CONF_PATH="/Users/mabecker/qnx710/host/darwin/x86_64/etc/qcc/gcc"
QNX_CONFIGURATION="/Users/mabecker/.qnx"
QNX_HOST="/Users/mabecker/qnx710/host/darwin/x86_64"
QNX_TARGET="/Users/mabecker/qnx710/target/qnx7"

# Clean the project
make -j15 clean
rm -fr build/aarch64le-debug

# Compile the project
make -j15 all
