# BZO Concept – Development

Development boards and libraries designed by **BZO Concept** to test circuits in real conditions.
These boards are used during development and are shared, complete and working, so anyone can study, build or reuse them.
This repository mirrors the *Développement* section of [bzo-concept.fr](https://www.bzo-concept.fr/developpement/).

## Boards (KiCad projects, PDF schematics, production files)

| Folder | Description |
|---|---|
| [UART_UPDI_Dongle](UART_UPDI_Dongle) | USB–UART / UPDI dongle for programming and debugging, with quick access to 5V, 3V3 and GND rails |
| [AVR32DD32_DevBoard](AVR32DD32_DevBoard) | Nano-sized AVR32DD32 board: 24 MHz internal oscillator, 23 ADCs, DAC, MVIO. Arduino IDE + [DxCore](https://github.com/SpenceKonde/DxCore) |
| [BigBoard_STM32F405](BigBoard_STM32F405) | Large STM32F405RGT6 test board: every useful pin on headers with LED drivers. Used to validate pin assignment, serial, CAN and firmware on BZO ECUs. Arduino IDE + [Arduino Core STM32](https://github.com/stm32duino/Arduino_Core_STM32) |
| [STM32F042F6P7_DevBoard](STM32F042F6P7_DevBoard) | Small STM32F042F6P7 (TSSOP-20, 48 MHz) board with USB–UART, programmable from Arduino IDE. Arduino IDE + [Arduino Core STM32](https://github.com/stm32duino/Arduino_Core_STM32) |

## Libraries (Arduino IDE)

| Folder | Description |
|---|---|
| [BZO_PWM_Generator](BZO_PWM_Generator) | Software PWM on any pin of any processor (ATtiny, ATmega, STM32…), 1–1000 Hz, duty or frequency modulation, 4 independent channels, no dependency |
| [TunerStudio_Library](TunerStudio_Library) | Universal TunerStudio communication library (and any `.ini` based software) for configuration and monitoring of custom modules. Bluetooth tested (MSDroid). Example sketch and `.ini` included |

## See also

ECU firmware, datasheets and tools: [BZO-Downloads](https://github.com/BZO-Concept/BZO-Downloads)
