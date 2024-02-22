# STM32F103C8 TFT Screen Benchmarking Project

## Overview

This project aims to benchmark the performance of interfacing an STM32F103C8 microcontroller with a TFT 128x160 screen using both standard SPI and SPI with DMA. The primary goal is to compare the time efficiency between these two methods for drawing graphics on the TFT screen.
## Project development
In this project, I have developed the following HAL & CMSIS peripheral drivers:
- SPI: for interfacing with the TFT ILI934 screen
- DMA: for using DMA channels with SPI for faster data transmission 
- Timer: Used for benchmarking by measuring the time taken to draw graphics on the screen
- GPIO: for sending control signals during the screen interface
- NVIC: To enable interrupts and apply interrupt-driven timer and DMA functionality
- Systick: for precise delay functionalities



## Usage

1. **Clone the Repository:**
    ```sh
    git clone https://github.com/MahmoudSheemy127/STM32F103C8-TFT-Screen-Benchmarking.git
    ```

2. **Hardware Connections:**
    - Connect the TFT screen to the specified GPIO pins on the STM32F103C8 as shown in the figure below.
    - In this project, I am using SPI2
    - Ensure proper power supply and ground connections.

3. **Application configurations:**
    - To start SPI DMA benchmarking set the macro flag ```TRANSFER_MODE``` to ```DMA_MODE```
    - To start normal SPI benchmarking set the macro flag ```TRANSFER_MODE``` to ```SPI_MODE```


3. **Build and Flash:**
    - Use your preferred STM32 development environment (e.g., STM32CubeIDE, PlatformIO) to build and flash the project to the microcontroller.

4. **Run the Benchmark:**
    The application will draw a series of graphics on the TFT screen.
    After drawing the graphics on the screen the final benchmark result of the SPI transfer method chosen is printed on the screen.

## Results

The benchmarking results demonstrate a significant reduction in time when using SPI with DMA for drawing graphics on the TFT screen.
Working with CLK_FREQ = 8Mhz & SPI_CLK = 2 Mhz

| BENCHMARK                               | SPI DMA    | SPI       |
| ----------------------------------------|------------|-----------|
| TOTAL DATA TRANSMITTED                   | 469 KB     | 469 KB    |
| TOTAL TIME TAKEN FOR DATA TRANSMISSION   | 453 ms     | 995 ms    |
| TRANSMISSION RATE                        | ~ 1 KB/ms  | ~ 484 Bytes/ms |

Conclusion: The benchmark test shows a reduction in transmission rate by 50% when DMA is used with SPI for drawing graphics on the TFT screen.


## Demonstration

For a complete Benchmark test demonstration check this [video](https://youtu.be/hMseklYoiG8)


## License

This project is licensed under the [MIT License](LICENSE).

---
