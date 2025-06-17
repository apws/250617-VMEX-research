
set PATH=%PATH%;c:\~sdk\PicoSDK\cmake\bin
set PICO_SDK_PATH=c:\~sdk\PicoSDK\pico-sdk
set PICO_TOOLCHAIN_PATH=c:\~sdk\PicoSDK\gcc-arm-none-eabi\bin
cmake -G "Unix Makefiles" -DPICO_COPY_TO_RAM=1 ..
make -j4



