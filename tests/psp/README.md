# TempAR Test App

`make test-app` builds `build/tempar-test/EBOOT.PBP`. Copy it to
`ms0:/PSP/GAME/TEMPARTEST/EBOOT.PBP` (or `ux0:/pspemu/PSP/GAME/TEMPARTEST/EBOOT.PBP` on Vita) and launch it with
TempAR enabled.

The app displays its current writable addresses and values. This makes it safe to test real, fake, and CWCheat
pointer codes without relying on an EBOOT being loaded at a fixed address.

## Test procedure

1. Launch the app, open TempAR with `R+HOME`, and confirm the menu opens without a freeze.
2. Use the memory browser or a temporary cheat to write each direct target; the displayed value must change.
3. For CWCheat `0x06`, use `slot 1` for a one-level pointer and `slot 2` for a two-level pointer. Both must resolve
   to `target`; test positive and negative offsets with 8-, 16-, and 32-bit writes.
4. Use `words` to test positive and inverse multi-write pointers. The four words provide an ordered, visible result.
5. Press `CROSS` with cheats disabled to restore the fixtures before each case. A malformed pointer must leave the
   app running.

`docs/tests/tests.db` remains the comprehensive parser/code-engine corpus. Its addresses are historical fixtures, so
copy individual cases into a temporary database and replace their addresses with those printed by this app.

## Compatibility matrix

Run the smoke test on a PSP and on current Adrenaline. On Adrenaline 8+, use the included
`src/resources/seplugins/plugins.txt` entries (installed as `ux0:/pspemu/seplugins/plugins.txt`). Also launch a PS1
title with `tempar_lite.prx` enabled and verify `R+HOME` opens TempAR; the test EBOOT itself is a PSP-mode test and
does not run under POPS.
