
export PICO_SDK_PATH=/mnt/c/~sdk/PicoSDK/pico-sdk
export PICO_TOOLCHAIN_PATH=/mnt/c/~sdk/PicoSDK/gcc-arm-none-eabi/bin
cmake -DPICO_COPY_TO_RAM=1 ..
make -j4

