# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.13.1)
set(BOARD nucleo_l432kc)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(stm32_pm_blinky)

# target_sources(app PRIVATE src/spi/transceive_master_double.cpp)
target_sources(app PRIVATE src/controller/controller.cpp)


target_include_directories(app PUBLIC external/PX4-Matrix)

