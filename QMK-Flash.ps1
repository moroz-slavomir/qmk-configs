$configFile= $args[0]
$keyboard = $args[1]

# Load config
$config = Get-Content -Raw -Path $configFile | ConvertFrom-Json
$config.keyboard = "handwired/slavomir/" + $keyboard

# Create temp file for edited config
$tempFile = New-TemporaryFile
$currentDir = Get-Location;
Set-Location $tempFile.Directory

# Write config to temp
$modifiedConfig = ConvertTo-Json $config
Add-Content -Path $tempFile -Value $modifiedConfig

# Compile firmware in wsl
$wslPath = wsl -- wslpath -a .
$wslFile = $wslPath + "/" + $tempFile.BaseName + $tempFile.Extension
$output = [string] (wsl -- ~/.local/bin/qmk flash $wslFile)

$output -match '(\S+\.hex)'
$hexFile = $Matches[0]
$wslQmkDir = wsl -- readlink -f ~/qmk_firmware
$winHexFile =  wsl -- wslpath -a -w $wslQmkDir/$hexFile

qmk_toolbox.exe flash m32u4 $winHexFile 

# Cleanup
Remove-Item -Path $tempFile
Set-Location $currentDir

