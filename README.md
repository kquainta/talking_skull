# talking_skull

Arduino sketch to run the Talking Skull project. This repository contains a single sketch: `talking_skull.ino`.

## Files
- `talking_skull.ino` — main Arduino sketch
- `.gitignore` — ignores editor files and Arduino build artifacts

## Inventory
- Arduino Nano
- KA2284 LED sound meter
	- (Shout out to jawduino at buttonbanger.com for this solution)
- Muizei MG90S servos (higher stall torque ~2.0 kg)

## Quick start

Requirements
- Arduino IDE (macOS) or `arduino-cli` (recommended for CLI builds)
- An Arduino Nano (ATmega328P) or compatible board

Using the Arduino IDE (GUI)
1. Open the Arduino IDE.
2. File → Open → select this repository folder (the `.ino` file).
3. Tools → Board → select "Arduino Nano" and choose the correct processor/bootloader (try "ATmega328P (Old Bootloader)" if uploads fail).
4. Tools → Port → select the Nano port (e.g. `/dev/tty.usbserial-XXXXX`).
5. Click Upload.

Using arduino-cli (recommended)
Install:

```zsh
brew install arduino-cli
arduino-cli core update-index
arduino-cli core install arduino:avr
```

Compile and upload from the project root:

```zsh
# Compile
arduino-cli compile --fqbn arduino:avr:nano $(pwd)

# Find the serial port (macOS)
ls /dev/tty.*

# Upload (replace /dev/tty.usbserial-XXXX with your port)
arduino-cli upload -p /dev/tty.usbserial-XXXX --fqbn arduino:avr:nano $(pwd)

# If you have an old-bootloader Nano, use:
arduino-cli compile --fqbn arduino:avr:nano:cpu=atmega328old $(pwd)
arduino-cli upload -p /dev/tty.usbserial-XXXX --fqbn arduino:avr:nano:cpu=atmega328old $(pwd)
```

VS Code task
This workspace already contains a task named "Arduino: Compile (Nano)" which runs:

```
arduino-cli compile --fqbn arduino:avr:nano ${workspaceFolder}
```

Troubleshooting
- If the serial port doesn't appear, your Nano may use the CH340 USB-serial chip — install the CH340 macOS driver and reconnect the board.
- Try the `atmega328old` CPU option if uploads fail due to bootloader baud differences.
- Use `-v` with `arduino-cli upload` for verbose output.

License
Add a license of your choice (MIT, GPL, etc.) — this repo does not include one by default.

---
Created and pushed from the local development environment.
