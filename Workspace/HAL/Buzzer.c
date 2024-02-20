/*
 * Buzzer.c
 *
 *  Created on: Feb 17, 2024
 *      Author: mw296
 */

#include "PWM.h"
#include "Buzzer.h"
#include "Ticker.h"


static char notes[] = "cdfda ag cdfdg gf";
static char beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};

char temp = 50;


static void Buzz(uint32_t freq, uint32_t duration)
{
	PWM_Freq(freq);
	PWM_Start();

	Ticker_ms(duration);
}

static int frequency(char note)
{

  int i;
  const int numNotes = 8;  // number of notes we're storing

  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};


  for (i = 0; i < numNotes; i++)
  {
    if (names[i] == note)
    {
      return(frequencies[i]);
    }
  }
  return(0);
}


void playNote(void)
{
	int i;
	int duration;
	for(i = 0 ; i < 18; i++)
	{
		duration = beats[i] * temp;
		if(notes[i] == ' ')
		{
			Ticker_ms(duration);
		}

		else {
			Buzz(frequency(notes[i]) , duration );
			Ticker_ms(duration );
		}
		Ticker_ms(temp / 10);
	}
	PWM_Duty(60000);
	PWM_Stop();

}


