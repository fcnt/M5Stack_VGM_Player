/**
 * @file YMF262.h
 * @author Taisuke Watanabe (famicom.neet@gmail.com)
 * @brief YMF262 driver header
 * @version 0.1
 * @date 2022-07-24
 *
 * @copyright Copyright (c) 2022 Taisuke Watanabe
 *
 */

#ifndef YMF262_DRV_H_
#define YMF262_DRV_H_

#define BUS_I2C 0
#define BUS_GPIO 1

#define GPIO_D0
#define GPIO_A0
#define GPIO_A1
#define GPIO_RST
#define GPIO_WR
#define GPIO_CS

#include <Arduino.h>
class YMF262 {
private:
  void rawWrite(uint8_t, uint8_t);

public:
  YMF262();
  void begin(uint8_t);
  void reset();
  void write0(uint8_t, uint8_t);
  void write1(uint8_t, uint8_t);
};

#endif