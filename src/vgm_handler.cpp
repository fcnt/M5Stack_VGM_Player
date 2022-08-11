/**
 * @file vgm_handler.cpp
 * @author Taisuke Watanabe (famicom.neet@gmail.com)
 * @brief VGM File handler
 * @version 0.1
 * @date 2022-08-11
 *
 * @copyright Copyright (c) 2022 Taisuke Watanabe
 *
 */

#include "vgm_handler.h"
#include "YMF262.h"

YMF262 myYM262 = YMF262();

VGMHandler::VGMHandler() {}
uint8_t VGMHandler::getVGM8(uint8_t *vgmDataBuf) { return vgmDataBuf[vgmPos]; }

uint16_t VGMHandler::getVGM16(uint8_t *vgmDataBuf) {
  return getVGM8(vgmDataBuf) + (getVGM8(vgmDataBuf) << 8);
}

uint32_t VGMHandler::getVGM32(uint8_t *vgmDataBuf) {
  return getVGM8(vgmDataBuf) + (getVGM8(vgmDataBuf) << 8) +
         (getVGM8(vgmDataBuf) << 16) + (getVGM8(vgmDataBuf) << 24);
}

int32_t VGMHandler::begin(File *vgmFp) {
  // vgm = SD.open(filename);
  if (vgm == NULL) {
    return false;
  } else {
    vgm = vgmFp;
    return true;
  }
}

uint32_t VGMHandler::getVGMPos() { return vgmPos; }
void VGMHandler::waitSpecified(uint16_t samples) {}
void VGMHandler::endParse() { vgm->close(); }

int32_t VGMHandler::playVGM() { return true; }

int32_t VGMHandler::parseVGM() {
  uint8_t vgmCMD;
  uint8_t chipData;
  uint8_t chipAddr;
  uint16_t data16;

  vgmCMD = getVGM8(vgmData);
  vgmPos++;

  switch (vgmCMD) {
  // for YMF262
  case 0x5E:
    chipData = getVGM8(vgmData);
    chipAddr = getVGM8(vgmData);
    myYM262.write0(chipAddr, chipData);
    vgmPos += 2;
    break;
  case 0x5F:
    chipData = getVGM8(vgmData);
    chipAddr = getVGM8(vgmData);
    myYM262.write1(chipAddr, chipData);
    vgmPos += 2;
    break;
  case 0x50:
    chipData = getVGM8(vgmData);
    chipAddr = getVGM8(vgmData);
    // SN76489.write(reg, data8);
    vgmPos += 2;
    break;
  case 0x61:
    data16 = getVGM16(vgmData);
    waitSpecified(data16);
    vgmPos += 2;
    break;
  case 0x62:
  case 0x63:
  case 0x66:
    endParse();
    break;
  default:
    vgmPos++;
    break;
  }
  return true;
}
