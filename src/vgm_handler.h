/**
 * @file vgm_handler.h
 * @author Taisuke Watanabe (famicom.neet@gmail.com)
 * @brief YMF262 driver header
 * @version 0.1
 * @date 2022-08-11
 *
 * @copyright Copyright (c) 2022 Taisuke Watanabe
 *
 */

#ifndef VGM_HEADER_H_
#define VGM_HEADER_H_

#include <Arduino.h>
#include <M5Stack.h>

typedef struct VGM_header {
  // for VGM ver1.70
  // 0x00
  uint32_t vgmIdent;
  uint32_t eofOffset;
  uint32_t version;
  uint32_t sn76489Clk;
  // 0x10
  uint32_t ym2413Clk;
  uint32_t gd3Offset;
  uint32_t totalSamples;
  uint32_t loopOffset;
  // 0x20
  uint32_t loopSamples;
  uint32_t rate;
  uint16_t snFeedback;
  uint8_t snShiftRegWid;
  uint8_t snFlags;
  uint32_t ym2612Clk;
  // 0x30
  uint32_t ym2151Clk;
  uint32_t vgmDataOffset;
  uint32_t segaPCMClk;
  uint32_t SPCMInterface;
  // 0x40
  uint32_t RF5C68Clk;
  uint32_t YM2203Clk;
  uint32_t YM2608Clk;
  uint32_t YM2610BClk;
  // 0x50
  uint32_t YM3812Clk;
  uint32_t YM3526Clk;
  uint32_t Y8950Clk;
  uint32_t YMF262Clk;
  // 0x60
  uint32_t YMF278BClk;
  uint32_t YMF271Clk;
  uint32_t YMZ280BClk;
  uint32_t RF5C164Clk;
  // 0x70
  uint32_t PWMClk;
  uint32_t AY8910Clk;
  uint8_t AYT;
  uint8_t AYFlags[3];
  uint8_t VM;
  uint8_t skip_01;
  uint8_t LB;
  uint8_t LM;
  // 0x80
  uint32_t GBDMGClk;
  uint32_t NESAPUClk;
  uint32_t MultiPCMClk;
  uint32_t uPD7759Clk;
  // 0x90
  uint32_t OKIM6258Clk;
  uint8_t OF;
  uint8_t KF;
  uint8_t CF;
  uint8_t skip_02;
  uint32_t OKIM6295Clk;
  uint32_t K051649Clk;
  // 0xA0
  uint32_t K054539Clk;
  uint32_t HuC6280Clk;
  uint32_t C140Clk;
  uint32_t K053260Clk;
  // 0xB0
  uint32_t PokeyClk;
  uint32_t QSoundClk;
  uint32_t SCSPClk;
  uint32_t ExtraHdrOfs;
  // 0xC0
  uint32_t WonderSwanClk;
  uint32_t VSUClk;
  uint32_t SAA1099Clk;
  uint32_t ES5503Clk;
  // 0xD0
  uint32_t ES5506Clk;
  uint16_t ESchns;
  uint8_t CD;
  uint8_t skip_03;
  uint32_t X1010Clk;
  uint32_t C352Clk;
  // 0xE0
  uint32_t GA20Clk;
  uint32_t skip_04[3];
  // 0xF0
  uint32_t skip_05[4];
} VGM_header_t;

typedef struct GD3_tag {
  // for GD3 ver1.00 tag
  uint16_t *enTrackName;
  uint16_t *jpTrackName;
  uint16_t *enGameName;
  uint16_t *jpGameName;
  uint16_t *enSystemName;
  uint16_t *jpSystemName;
  uint16_t *enAuthor;
  uint16_t *jpAuthor;
  uint16_t *releaseDate;
  uint16_t *dataConverter;
  uint16_t *memo;
} GD3_tag_t;

typedef struct VGMFile {
  VGM_header_t *pVGMHeader;
  GD3_tag_t *pGD3_tag_t;
  uint8_t *data;
} VGMFile_t;

class VGMHandler {
private:
  uint8_t *vgmData;
  File *vgm;
  uint32_t vgmPos = 0;

  VGM_header_t *pVGMHeader;
  GD3_tag_t *pGD3_tag_t;

  uint8_t getVGM8(uint8_t *);
  uint16_t getVGM16(uint8_t *);
  uint32_t getVGM32(uint8_t *);
  void waitSpecified(uint16_t);
  void endParse();

public:
  VGMHandler();
  int32_t begin(File *);
  int32_t parseVGMHeader(uint8_t *);
  uint32_t getVGMDataOffset();
  int32_t parseVGM();
  int32_t playVGM();
  uint32_t getVGMPos();
};

#endif
