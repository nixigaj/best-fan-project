# Best fan project

Erik Junsved, Hanna Lindmark, Jonna Bauer, Tove Frænell

A temperature controlled fan with PWM.

## Dev setup

This project uses PlatformIO as build tool.

[Install PlatformIO core](https://docs.platformio.org/en/latest/core/installation/methods/index.html)

### Needed VSCode extensions

- [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)
- [EditorConfig](https://marketplace.visualstudio.com/items?itemName=EditorConfig.EditorConfig)

### Needed CLion extensions
- [PlatformIO](https://plugins.jetbrains.com/plugin/13922-platformio-for-clion)
- [EditorConfig](https://plugins.jetbrains.com/plugin/7294-editorconfig)

## Building and running
Connect the Arduino Uno to a USB-port. Then, use the buttons in your editor or run `pio run -t upload -t monitor -e uno` to upload, execute, and monitor the program over serial.
