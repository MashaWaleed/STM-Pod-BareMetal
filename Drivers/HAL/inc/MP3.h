/*
 * MP3.h
 *
 * Author: Mohamed Waleed
 */

#ifndef MP3_H_
#define MP3_H_


void Send_cmd (uint8_t cmd, uint8_t Parameter1, uint8_t Parameter2);

void HAL_DF_Init (uint8_t volume);
void HAL_DF_Next (void);
void HAL_DF_Pause (void);
void HAL_DF_Previous (void);
void HAL_DF_Playback (void);
void HAL_DF_SpecifyVolume(uint8_t volume);
void HAL_DF_SpecifyTrack(uint8_t track);


#endif /* MP3_H_ */
