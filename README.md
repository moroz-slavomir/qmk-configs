# qmk-configs

## setup

### wsl
```
git clone git@github.com:moroz-slavomir/qmk_firmware.git qmk
cd qmk
git submodule update --init --recursive
sudo apt-get install avr-libc gcc-avr python3 python3-pip && python3 -m pip install qmk
source ~/.bashrc
qmk setup --no
ln -s $PWD ~/qmk_firmware
make git-submodule
```

### windows
install [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) with drivers

## usage
Download json config from [QMK Configurator](https://config.qmk.fm/#/handwired/dactyl_manuform/6x6/LAYOUT_6x6)

`$ QMK-Flash.ps1 <json> <keyboard>`

`$ QMK-Flash.ps1 .\manuform_6x6_default.json proto_1`

![Sample](https://github.com/moroz-slavomir/qmk-configs/raw/master/Sample.PNG)
