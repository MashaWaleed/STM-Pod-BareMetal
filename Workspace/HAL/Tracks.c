/*
 * Tracks.c
 *
 *  Created on: Feb 12, 2024
 *      Author: mw296
 */

#include "Tracks.h"

const char *trackNames[MAX_TRACK_NUM] = { "Genesis", "Mem Reboot",
		"Rapp Snitch", "Killin' on demand" };

const int duration[MAX_TRACK_NUM] = { 255, 236, 173, 129 };


const char* getTrackName(uint8_t trackNumber) {
	return trackNames[trackNumber];

}
