# Raspberry Pi 4 Buildroot System Monitor

A custom embedded Linux image for the Raspberry Pi 4, built with Buildroot. It includes my own package, sysmon, which starts at boot and prints uptime, CPU temperature and free memory to the console every 5 seconds.


https://github.com/user-attachments/assets/dc15275e-0d1f-4c7d-9bd7-956fffb57e24


The package is kept outside the Buildroot tree as a BR2_EXTERNAL, so Buildroot itself is not modified. sysmon is cross-compiled for ARM64 by the Buildroot toolchain.

## Build

```
git clone --depth 1 --branch 2026.08.1 https://gitlab.com/buildroot.org/buildroot.git
cd buildroot
make BR2_EXTERNAL=/path/to/rpi4-buildroot-sysmon rpi4_sysmon_defconfig
make
```

The image is written to `output/images/sdcard.img`. Flash it to a microSD card and connect a USB-TTL adapter to GPIO14/15 at 115200 baud to see the console. Log in as root with no password.

## Files

- `package/sysmon`: the Buildroot package and its init script
- `src/sysmon`: the program
- `configs/rpi4_sysmon_defconfig`: Raspberry Pi 4 config with sysmon enabled
