/**
 * @file YMF262.cpp
 * @author Taisuke Watanabe (famicom.neet@gmail.com)
 * @brief YMF262 driver
 * @version 0.1
 * @date 2022-07-24
 *
 * @copyright Copyright (c) 2022 Taisuke Watanabe (famicom.neet@gmail.com)
 *
 */

#include "ymf262.h"

YMF262::YMF262() {}
void YMF262::begin(uint8_t busType) {
  if (busType == BUS_I2C) {
  } else if (busType == BUS_GPIO) {
  }
}
void YMF262::reset() {}
void YMF262::write0(uint8_t addr, uint8_t data) {}
void YMF262::write1(uint8_t addr, uint8_t data) {}
