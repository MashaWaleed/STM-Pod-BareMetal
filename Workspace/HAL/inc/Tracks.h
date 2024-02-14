/*
 * Tracks.h
 *
 *  Created on: Feb 12, 2024
 *      Author: mw296
 */

#ifndef INC_TRACKS_H_
#define INC_TRACKS_H_

#include "stdint.h"

#define MAX_TRACK_NUM        4
extern const char *trackNames[MAX_TRACK_NUM];
extern const int duration[MAX_TRACK_NUM];

const char* getTrackName(uint8_t trackNumber);


#endif /* INC_TRACKS_H_ */
