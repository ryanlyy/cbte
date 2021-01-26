#!/bin/bash

set -e

export KERNEL_VERSION="${KERNEL_VERSION:-$(uname -r)}"
export kernel_version="$(echo "${KERNEL_VERSION}" | awk -vFS=- '{ print $1 }')"
export major_version="$(echo "${KERNEL_VERSION}" | awk -vFS=. '{ print $1 }')"

yum install -y bc curl flex bison elfutils-libelf-devel

mkdir -p /usr/src/linux
curl -sL "https://www.kernel.org/pub/linux/kernel/v${major_version}.x/linux-$kernel_version.tar.gz"     | tar --strip-components=1 -xzf - -C /usr/src/linux
cd /usr/src/linux
#zcat /proc/config.gz > .config
cp /boot/config-$(uname -r)} .
make ARCH=x86 oldconfig
make ARCH=x86 prepare
mkdir -p /lib/modules/$(uname -r)
ln -sf /usr/src/linux /lib/modules/$(uname -r)/source
ln -sf /usr/src/linux /lib/modules/$(uname -r)/build
