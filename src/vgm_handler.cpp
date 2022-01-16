#include "vgm_handler.h"

uint8_t *vgmData;
File vgm;

uint8_t getVGM8(uint8_t *vgmDataBuf) { return vgmDataBuf[vgmPos]; }

uint16_t getVGM16(uint8_t *vgmDataBuf) {
  return getVGM8(vgmDataBuf) + (getVGM8(vgmDataBuf) << 8);
}

uint32_t getVGM32(uint8_t *vgmDataBuf) {
  return getVGM8(vgmDataBuf) + (getVGM8(vgmDataBuf) << 8) +
         (getVGM8(vgmDataBuf) << 16) + (getVGM8(vgmDataBuf) << 24);
}

uint8_t openVGM(uint8_t *filename) {
  vgm = SD.open(filename);
  if (vgm == NULL) {
    return NULL;
  } else {
    return TRUE;
  }
}

uint32_t playVGM() { parseVGM(); }

uint32_t parseVGM() {
  uint8_t cmd;
  uint8_t reg;
  uint8_t data8;
  uint16_t data16;

  cmd = getVGM8();

  switch (cmd) {
  // for YMF262
  case 0x5E:
    data16 = getVGM16();
    YMF262.write0(data16);
    break;
  case 0x5F:
    data16 = getVGM16();
    YMF262.write1(data16);
    break;
  case 0x50:
    reg = getVGM8(vgmData);
    data = getVGM8(vgmData);
    SN76489.write(reg, data8);
    break;
  case 0x61:
    wait();
    break;
  case 0x62:
  case 0x63:
  case 0x66:
    end();
    break;
  }
}
