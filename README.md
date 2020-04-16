# qmk-configs

## setup

### wsl
```
git clone git@github.com:moroz-slavomir/qmk_firmware.git qmk
cd qmk
git submodule update --init --recursive
sudo apt-get install avr-libc gcc-avr python3 python3-pip && python3 -m pip install qmk
qmk setup --no
ln -s $PWD ~/qmk_firmware
make git-submodule
```

### windows
install [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) with drivers


