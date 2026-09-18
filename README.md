## TempAR

##### Overview

TempAR is a cheat plugin for the PlayStation Portable.

It is a heavily modified version of MKUltra which itself is a modified version of NitePR.

## Origins and third-party code

TempAR builds on several PSP-scene projects and retains their source attributions:

- **NitePR** by SANiK, imk, and telazorn, via **MKUltra** by RedHate and NoEffex, supplied the original cheat-device
  code and design.
- **[PSPLINK](https://github.com/tyranid/psplinkusb)** by James Forshaw (TyRaNiD), Julian T, Rasmus B, and John
  Kelley supplied the debug/impose menu, disassembler, and floating-point formatting code. These BSD-licensed notices
  are reproduced in [docs/LICENSE](docs/LICENSE).
- **[PSPSDK](https://github.com/pspdev/pspsdk)** supplied SDK-derived headers and the on-screen keyboard helper; their
  source headers retain the original copyright and licence notices.
- TempAR supports the **CWCheat** format and includes its SDK interface by weltall.

See the full acknowledgements in the [plugin guide](docs/README.md#thanks).

## Install

TempAR requires PSP custom firmware with plugin support; it does not run on official firmware.

1. Download and extract the release archive, or build one as described below.
2. Copy its `seplugins` directory to the root of the PSP Memory Stick. On a PS Vita running Adrenaline, copy it to
   `ux0:/pspemu/`, so the resulting files are:

   ```text
   PSP:      ms0:/seplugins/TempAR/tempar.prx
   PS Vita:  ux0:/pspemu/seplugins/TempAR/tempar.prx
   ```

3. Register the appropriate plugin entry. PSP paths inside the PSP environment use `ms0:` on both a PSP and a Vita.
   The archive supplies ready-made classic `game.txt` and `pops.txt`; if you already have either file, append the
   relevant line instead of replacing it:

   ```text
   # PSP games: ms0:/seplugins/game.txt
   ms0:/seplugins/TempAR/tempar.prx 1

   # Classic Adrenaline configuration: ux0:/pspemu/seplugins/game.txt
   ms0:/seplugins/TempAR/tempar.prx 1

   # PS1/POPS games: ms0:/seplugins/pops.txt
   ms0:/seplugins/TempAR/tempar_lite.prx 1

   # Classic Adrenaline configuration: ux0:/pspemu/seplugins/pops.txt
   ms0:/seplugins/TempAR/tempar_lite.prx 1
   ```

   Adrenaline 8 and Epinephrine use `ux0:/pspemu/seplugins/plugins.txt` instead. The release includes this file;
   copy it if you do not already have one, otherwise add these entries (or use their Plugin Manager):

   ```text
   psp, ms0:/seplugins/TempAR/tempar.prx, on
   pops, ms0:/seplugins/TempAR/tempar_lite.prx, on
   ```

4. Restart the game (or reboot the PSP). Press `R+HOME` in-game to open TempAR.

### Cheat database

TempAR includes a `cheat.db`. For a newer CWCheat database, download [`cheat.db` from CWCheat Database Plus](https://github.com/Saramagrean/CWCheat-Database-Plus-/raw/refs/heads/master/cheat.db) and replace
`ms0:/seplugins/TempAR/cheat.db` (or `ux0:/pspemu/seplugins/TempAR/cheat.db` on PS Vita).

See the [plugin guide](docs/README.md) for controls, cheat formats, and configuration details.

## Build from source

To compile, ensure you have Docker installed and run the following in PowerShell:

```
docker run --rm -it -v "${PWD}:/src" -w "/src" ticky/pspdev make release
```

A tar.gz file containing the binaries and other misc files will be output to a `build` folder.

The release archive is written to `build/tempar-<version>.tar.gz`.
