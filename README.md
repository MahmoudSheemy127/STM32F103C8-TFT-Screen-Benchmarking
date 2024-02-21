# STM32F103C8 TFT Screen Benchmarking Project

## Overview

This project is aimed at benchmarking the performance of interfacing an STM32F103C8 microcontroller with a TFT 128x160 screen using both standard SPI and SPI with DMA. The primary goal is to compare the time efficiency between these two methods for drawing graphics on the TFT screen.
## Project development
In this project i have developed the following HAL & CMSIS peripheral drivers:
- SPI: for interfacing with the TFT ILI934 screen
- DMA: for using DMA channels with SPI for faster data transmission 
- Timer: Used for benchmarking by measuring the time taken to draw graphics on the screen
- GPIO: for sending control signals during the screen interface
- NVIC: To enable interrupts and apply interrupt driven timer and dma functionality
- Systick: for percise delay functionalities



## Usage

1. **Clone the Repository:**
    ```sh
    git clone https://github.com/MahmoudSheemy127/STM32F103C8-TFT-Screen-Benchmarking.git
    ```

2. **Hardware Connections:**
    - Connect the TFT screen to the specified GPIO pins on the STM32F103C8 as shown in the figure below.
    - In this project i am using SPI2
    - Ensure proper power supply and ground connections.

3. **Application configurations:**
    - To start SPI DMA benchmarking set the flag '''TRANSFER_MODE


3. **Build and Flash:**
    - Use your preferred STM32 development environment (e.g., STM32CubeIDE, PlatformIO) to build and flash the project to the microcontroller.

4. **Run the Benchmark:**
    - Monitor the serial output or other designated channels to view the benchmark results.

## Results

The benchmarking results demonstrate a significant reduction in time when using SPI with DMA for drawing graphics on the TFT screen.

## License

This project is licensed under the [MIT License](LICENSE).

---
