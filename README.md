# STM32F103C8 TFT Screen Benchmarking Project

## Overview

This project is aimed at benchmarking the performance of interfacing an STM32F103C8 microcontroller with a TFT 128x160 screen using both standard SPI and SPI with DMA. The primary goal is to compare the time efficiency between these two methods for drawing graphics on the TFT screen.

## Phases

### 1. Project Setup

- **STM32F103C8 Configuration:** Set up the STM32F103C8 microcontroller, configure GPIO pins, and initialize the necessary peripherals for SPI, DMA, Systick, and Timer.

- **TFT Screen Connection:** Wire the TFT 128x160 screen to the STM32F103C8, ensuring proper connections for control signals and SPI communication.

### 2. SPI Driver Implementation

- **SPI Initialization:** Develop a robust SPI driver to initialize the SPI peripheral with desired configurations.

- **Graphic Drawing Functions:** Implement functions for drawing basic graphics on the TFT screen using standard SPI.

### 3. DMA Driver Implementation

- **DMA Initialization:** Develop a DMA driver to set up DMA channels for efficient data transfer between memory and peripherals.

- **Enhanced Graphic Drawing Functions:** Enhance graphic drawing functions to leverage DMA for faster transmission.

### 4. Systick for Delay

- **Systick Timer:** Implement Systick timer functionality for precise delays in the project.

### 5. Timer for Benchmarking

- **Timer Configuration:** Configure a Timer peripheral to measure the time taken for graphic drawing operations.

- **Benchmarking Functions:** Implement functions to capture and log benchmarking results.

### 6. Main Application

- **SPI vs. SPI with DMA Comparison:** Develop a main application that utilizes both SPI and SPI with DMA to draw graphics on the TFT screen.

- **Benchmarking Execution:** Execute the benchmarking functions and compare the time efficiency between the two methods.

### 7. Documentation

- **README.md:** Create a comprehensive README file to guide users, developers, and contributors about the project, its purpose, setup, and results.

## Usage

1. **Clone the Repository:**
    ```sh
    git clone https://github.com/yourusername/stm32-tft-benchmark.git
    ```

2. **Hardware Connections:**
    - Connect the TFT screen to the specified GPIO pins on the STM32F103C8.
    - Ensure proper power supply and ground connections.

3. **Build and Flash:**
    - Use your preferred STM32 development environment (e.g., STM32CubeIDE, PlatformIO) to build and flash the project to the microcontroller.

4. **Run the Benchmark:**
    - Monitor the serial output or other designated channels to view the benchmark results.

## Results

The benchmarking results demonstrate a significant reduction in time when using SPI with DMA for drawing graphics on the TFT screen. Detailed results and charts may be found in the documentation or the project's wiki.

## License

This project is licensed under the [MIT License](LICENSE).

---