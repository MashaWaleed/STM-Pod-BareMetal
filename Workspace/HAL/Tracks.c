/*
 * Tracks.c
 *
 *  Created on: Feb 12, 2024
 *      Author: mw296
 */

#include "Tracks.h"

const char *trackNames[MAX_TRACK_NUM] = { "Genesis", "Mem Reboot",
		"Rapp Snitch", "Atlas", "Faded", "Nosebleed", "After image", "Dream Head", "Imagine", "Focus" };

const int duration[MAX_TRACK_NUM] = { 255, 236, 173, 188, 199, 234, 240, 199, 245, 235};


const char* getTrackName(uint8_t trackNumber) {
	return trackNames[trackNumber];

}
