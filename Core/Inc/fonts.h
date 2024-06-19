/*
 * font.h
 *
 *  Created on: Jun 16, 2024
 *      Author: Utilisateur
 */

#ifndef INC_FONTS_H_
#define INC_FONTS_H_

#include "stdint.h"

typedef struct
{
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;

} sFONT;


extern sFONT FONT_CO2;
extern sFONT FONT_TIME;
extern sFONT FONT_INFO;

#endif /* INC_FONTS_H_ */
