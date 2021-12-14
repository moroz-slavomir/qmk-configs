if ($args.Count -eq 0) { 
  Write-Host "Usage: qmk-flash [json] [keyboard]"
  Exit
}

$configFile= $args[0]
$keyboard = $args[1]

# Load config
$config = Get-Content -Raw -Path $configFile | ConvertFrom-Json
$config.keyboard = $keyboard

# Create temp file for edited config
$tempFile = New-TemporaryFile
$currentDir = Get-Location;
Set-Location $tempFile.Directory

# Write config to temp
$modifiedConfig = ConvertTo-Json $config
Add-Content -Path $tempFile -Value $modifiedConfig

# Compile firmware in wsl
$wslPath = wsl -- wslpath -a .
$wslFile = $wslPath + $tempFile.BaseName + $tempFile.Extension
$output = [string] (wsl -- PATH="~/.local/bin/" qmk compile $wslFile)

$output -match '(\S+\.hex)'
$hexFile = $Matches[0]
$wslQmkDir = wsl -- readlink -f ~/qmk_firmware
$winHexFile =  wsl -- wslpath -a -w $wslQmkDir/$hexFile

# Cleanup
Remove-Item -Path $tempFile
Set-Location $currentDir
Copy-Item -Path $winHexFile -Destination . 

# Flash
qmk_toolbox.exe $winHexFile | Out-Default
