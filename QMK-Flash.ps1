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
$wslPath = wsl -- echo "`$PWD"
$wslFile = $wslPath + "/" + $tempFile.BaseName + $tempFile.Extension
$output = [string] (wsl -- ~/.local/bin/qmk flash $wslFile)

$output -match '(\S+\.hex)'
$hexFileName = $Matches[0]
if($hexFileName) {
    wsl -- mv ~/qmk_firmware/$hexFileName firmware.hex
}

# Cleanup
Remove-Item -Path $tempFile
Remove-Item -Path firmware
Set-Location $currentDir

