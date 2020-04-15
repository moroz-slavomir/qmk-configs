# qmk-configs

## setup
```
git clone git@github.com:moroz-slavomir/qmk_firmware.git qmk
cd qmk
git submodule add git@github.com:moroz-slavomir/qmk-configs.git keyboards/handwired/slavomir
sudo apt-get install python3 python3-pip && python3 -m pip install qmk
qmk setup
```

## layout
`qmk json2c -o keyboards/handwired/slavomir/proto_1/keymaps/default/keymap.c` [layout.json](https://config.qmk.fm/#/handwired/dactyl_manuform/6x6/LAYOUT_6x6)

