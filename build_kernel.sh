#!/bin/bash
#Set up the environment

# cross compiler path
make clean && make mrproper
rm -rf KernelSU
rm -rf drivers/kernelsu
curl -LSs "https://raw.githubusercontent.com/tiann/KernelSU/main/kernel/setup.sh" | bash -s main
export PATH=$PATH:/home/anurag/Downloads/Clang-18.0.0-20230821/bin/
export CC=clang
export CLANG_TRIPLE=aarch64-linux-gnu-
export CROSS_COMPILE=aarch64-linux-gnu-
export CROSS_COMPILE_ARM32=arm-linux-gnueabi-

export ARCH=arm64
export SUBARCH=arm64
# export DTC_EXT=dtc

if [ ! -d "out" ];
then
	mkdir out
fi

date="$(date +%Y.%m.%d-%I:%M)"


make ARCH=arm64 O=out CC=clang lineage-nashc_defconfig
# Define the number of compilation threads
make ARCH=arm64 O=out CC=clang -j$(nproc --all) 2>&1 | tee kernel_log-${date}.txt
