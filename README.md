# Update firmware for QMK-based keyboards on Windows

# Prerequisities to compile keyboard firmware

## Install linux subsystem in Windows
1. Install wsl (if not installed before)
   - `wsl --install` 
2. After reboot "ubuntu" should install. If not search "Ubuntu" in MS Store and hit install.
   - Set user name and password (don't forget the password you set).
3. Install Window Terminal from Microsoft Store to work with Ubuntu command line
   - Open Windows Terminal and select Ubuntu in menu. 
4. Move to linux home folder
   - `cd ~`
5. Make Ubuntu up to date
   - `sudo apt update` 
   - `sudo apt upgrade`
6. Install Python 
   - `sudo apt install python3 python3-pip ipython3`

## Install QMK firmware in Linux subsystem
6. Install qmk
   - `python3 -m pip install --user qmk`
- Add path to ./.bashrc
    - `explorer.exe .` opens current folder. 
    - Edit .bashrc: append line `PATH="$HOME/.local/bin:$PATH"`
    - Reload bashrc to understand path `source ./.bashrc`
7. Load qmk_firmware repo
  - `qmk setup moroz-slavomir/qmk_firmware` OR `qmk setup [your-git-repository]`

## Download flash tool for windows
Create a folder somewhere and download the following files into
- download qmk_toolbox.exe
  - https://github.com/qmk/qmk_toolbox/releases
- qmk-flash.ps1 
  - https://github.com/moroz-slavomir/qmk-configs
- add the folder to PATH environment variable in Windows.
- run qmk_toolbox.exe for the first time. Install drivers when prompted.


# Update firmware

## Update keyboard mapping
- https://config.qmk.fm/#/


## Generate firmware 

run in powershell:
`qmk-flash.ps1 [KEYMAP.JSON] [KEYBOARD]`

e.g. `qmk-flash.ps1 .\manuform_6x6.json handwired/slavomir/proto_1`

> prerequisites
> 
> custom scripts enabled in PowerShell: `Set-ExecutionPolicy unrestricted`


## Flash keyboard

1. qmk_toolbox.exe is opened when you run `generate firmware`
2. double-check your settings
   - MCU is `atmega32u4`
   - autoflash is on
3. Press reset combination on left side keyboard, while USB is in the left side
4. Press reset combination on rigth side keyboard, while USB is in the right side

