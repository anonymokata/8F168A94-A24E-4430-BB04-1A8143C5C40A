#! /bin/bash
# only allow root to run this script
if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi

echo 'installing development toolchains'
apt-get install -y automake autoconf libtool pkg-config texinfo gcc make splint valgrind vim 

echo 'building check-0.10.0 from source'
cd check-0.10.0
autoreconf --install
./configure && make && make install

