# arduino-cs2-auto-accept

An Arduino Leonardo/Micro sketch that automatically clicks the **ACCEPT** button when a Counter-Strike 2 match is found.

Toggle it with **Scroll Lock**. While Scroll Lock is on, the Arduino moves the mouse pointer to the ACCEPT button and clicks it every 2 seconds. It moves the pointer before every click, so it still hits the button if you bump the mouse.

## Requirements

- An Arduino with native USB, such as the Leonardo or Pro Micro (ATmega32U4)
- The [HID-Project](https://github.com/NicoHood/HID) library by NicoHood, which you can install from the Arduino IDE Library Manager

## Usage

1. Open `arduino-cs2-auto-accept.ino` in the Arduino IDE and upload it to the board.
2. Plug the board into the PC. It shows up as a mouse and a keyboard.
3. Queue for a match in CS2 and turn **Scroll Lock** on.
4. Turn Scroll Lock off once the match is accepted.

## Configuration

These constants are at the top of the sketch:

| Constant               | Default        | Description                                       |
| ---------------------- | -------------- | ------------------------------------------------- |
| `SCREEN_W`, `SCREEN_H` | `1920`, `1080` | The resolution CS2 runs at                        |
| `TARGET_X`, `TARGET_Y` | `960`, `450`   | The center of the ACCEPT button, in game pixels   |
| `CLICK_INTERVAL_MS`    | `2000`         | The time between clicks                           |
| `SETTLE_MS`            | `40`           | The pause between moving the pointer and clicking |
| `PRESS_MS`             | `60`           | How long the left button stays pressed            |

## How it works

The board acts as an **absolute** pointing device, like a drawing tablet. It sends screen-relative coordinates, so Windows pointer speed and acceleration have no effect. The coordinates are normalized to the screen, so the defaults work whenever the game fills the primary monitor with a 16:9 resolution, even if the monitor's native resolution is different.

## Notes

- On multi-monitor setups, an absolute pointer is mapped across the whole virtual desktop, so the target may need adjusting.
- During the build, HID-Project prints `#pragma message: Using default ASCII layout for keyboard modules`. This is an informational note from the library, not a warning.
- Some keyboards have no Scroll Lock key. On HP EliteBook laptops, use **Fn + C**.

## License

[MIT](LICENSE)
