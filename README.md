## TempAR

##### Overview

TempAR is a cheat plugin for the PlayStation Portable.

It is a heavily modified version of MKUltra which itself is a modified version of NitePR.

## Install

TempAR requires PSP custom firmware with plugin support; it does not run on official firmware.

1. Download and extract the release archive, or build one as described below.
2. Copy its `seplugins` directory to the root of the PSP Memory Stick or PS Vita `ux0:` storage. The resulting plugin
   paths must be:

   ```text
   PSP:      ms0:/seplugins/TempAR/tempar.prx
   PS Vita:  ux0:/seplugins/TempAR/tempar.prx
   ```

3. Register the appropriate plugin entry. The archive supplies ready-made `game.txt` and `pops.txt`; if you already
   have either file, append the relevant line instead of replacing it:

   ```text
   # PSP games: ms0:/seplugins/game.txt
   ms0:/seplugins/TempAR/tempar.prx 1

   # PS Vita games: ux0:/seplugins/game.txt
   ux0:/seplugins/TempAR/tempar.prx 1

   # PS1/POPS games: ms0:/seplugins/pops.txt
   ms0:/seplugins/TempAR/tempar_lite.prx 1

   # PS1/POPS on PS Vita: ux0:/seplugins/pops.txt
   ux0:/seplugins/TempAR/tempar_lite.prx 1
   ```

4. Restart the game (or reboot the PSP). Press `R+HOME` in-game to open TempAR.

### Cheat database

TempAR includes a `cheat.db`. For a newer CWCheat database, download [`cheat.db` from CWCheat Database Plus](https://github.com/Saramagrean/CWCheat-Database-Plus-/raw/refs/heads/master/cheat.db) and replace
`ms0:/seplugins/TempAR/cheat.db` (or `ux0:/seplugins/TempAR/cheat.db` on PS Vita).

See the [plugin guide](docs/README.md) for controls, cheat formats, and configuration details.

## Build from source

To compile, ensure you have Docker installed and run the following in PowerShell:

```
docker run --rm -it -v "${PWD}:/src" -w "/src" ticky/pspdev make release
```

A tar.gz file containing the binaries and other misc files will be output to a `build` folder.

The release archive is written to `build/tempar-<version>.tar.gz`.
