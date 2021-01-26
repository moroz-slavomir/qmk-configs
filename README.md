# qmk-configs

## setup

### wsl
```
sudo apt-get install avr-libc gcc-avr python3 python3-pip && python3 -m pip install qmk
(reset terminal)

git clone git@github.com:moroz-slavomir/qmk_firmware.git qmk
cd qmk
git submodule update --init --recursive --remote
qmk setup
ln -s $PWD ~/qmk_firmware
```

### windows
install [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) with drivers

## usage
Download json config from [QMK Configurator](https://config.qmk.fm/#/handwired/dactyl_manuform/6x6/LAYOUT_6x6)

`$ QMK-Flash.ps1 <json> <keyboard>`

`$ QMK-Flash.ps1 .\manuform_6x6_default.json proto_1`

![Sample](https://github.com/moroz-slavomir/qmk-configs/raw/master/Sample.PNG)
