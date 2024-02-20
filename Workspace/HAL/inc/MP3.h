/*
 * MP3.h
 *
 * Author: Mohamed Waleed
 */

#ifndef MP3_H_
#define MP3_H_


#define TF_ONLINE  1
#define TF_OFFLINE 0

void Send_cmd (uint16_t cmd, uint16_t Parameter1, uint16_t Parameter2);

uint8_t HAL_DF_Init (uint8_t volume);
void HAL_DF_Next (void);
void HAL_DF_Pause (void);
void HAL_DF_Previous (void);
void HAL_DF_Playback (void);
void HAL_DF_SpecifyVolume(uint8_t volume);
void HAL_DF_SpecifyTrack(uint8_t track);
void HAL_DF_Wait_Push (void);


#endif /* MP3_H_ */
