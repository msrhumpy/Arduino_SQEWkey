/*
 *  (SQEW-KEY) SQuarE-Wave KEYboard feat. Arduino uno
 * 
 *  # Ver. 0.1(20141124)
 */

#include "notemap.h"

// logical PIN ASSIGN !! FIXME for your system!
#define SENSE_PIN 2 // sense pin for interrupt call-up
                    // NOTE! No use sense_pin for other use!
#define SOUND_PIN 8 // speaker pin

#define MILLION 1000000

// global variables
  volatile int   sw          = -1;
  volatile int   tmpNote     = 0;
  volatile int   tmpNoteLOW  = 0;
  volatile int   tmpNoteHIGH = 0;
  volatile int   Repeats     = 0;
  volatile float duty_rate = 0.5; // initial duty rate is half-half

/* INITIALIZE */
void setup()
{
  pinMode(SENSE_PIN, OUTPUT);
  pinMode(SOUND_PIN, OUTPUT);
  attachInterrupt(0, setSound, RISING); // using PIN#2 (1st arg: 0) for interrupt toggle
  Serial.begin(9600);
}

/*
 *    setSound() function:
 * 
 * - Setting current note and pitch.
 * - This function is called by interrupt-routine,
 *   if you send key inputs by serial communications.
 * 
 */
void setSound()
{
  switch (sw) {
    // scale 4-5 (key: z-.)
    case 'z': tmpNote = NOTE_C4;  break;
    case 's': tmpNote = NOTE_CS4; break;
    case 'x': tmpNote = NOTE_D4;  break;
    case 'd': tmpNote = NOTE_DS4; break;
    case 'c': tmpNote = NOTE_E4;  break;
    case 'v': tmpNote = NOTE_F4;  break;
    case 'g': tmpNote = NOTE_FS4; break;
    case 'b': tmpNote = NOTE_G4;  break;
    case 'h': tmpNote = NOTE_GS4; break;
    case 'n': tmpNote = NOTE_A4;  break;
    case 'j': tmpNote = NOTE_AS4; break;
    case 'm': tmpNote = NOTE_B4;  break;
    case ',': tmpNote = NOTE_C5;  break;
    case 'l': tmpNote = NOTE_CS5; break;
    case '.': tmpNote = NOTE_D5;  break;
    // scale 5-6 (key: w-p)
    case 'w': tmpNote = NOTE_C5;  break;
    case '3': tmpNote = NOTE_CS5; break;
    case 'e': tmpNote = NOTE_D5;  break;
    case '4': tmpNote = NOTE_DS5; break;
    case 'r': tmpNote = NOTE_E5;  break;
    case 't': tmpNote = NOTE_F5;  break;
    case '6': tmpNote = NOTE_FS5; break;
    case 'y': tmpNote = NOTE_G5;  break;
    case '7': tmpNote = NOTE_GS5; break;
    case 'u': tmpNote = NOTE_A5;  break;
    case '8': tmpNote = NOTE_AS5; break;
    case 'i': tmpNote = NOTE_B5;  break;
    case 'o': tmpNote = NOTE_C6;  break;
    case '0': tmpNote = NOTE_CS6; break;
    case 'p': tmpNote = NOTE_D6;  break;
    default:  tmpNote =    0; break;
  }
  // set tmporal note pitches and number of repeats (duration)
  tmpNoteHIGH = (MILLION / tmpNote) * duty_rate;
  tmpNoteLOW = (MILLION /tmpNote) * (1 - duty_rate);
  Repeats = tmpNote >> 2; // "2" is Magic No. (moderate duration)
}

/* MAIN ROUTINE */
void loop()
{
  int i;
  sw = Serial.read();     // key input check
  if (sw != -1) {         // if detecting input:
    if ( (sw == '+') && (duty_rate < 0.8) ) { 
      duty_rate += 0.125; // ___|^^^ => __|^^^^ => _|^^^^
    } else if ( (sw == '-') && (duty_rate > 0.2) ) { 
      duty_rate -= 0.125; // ___|^^^ => ____|^^ => ____|^
    } else {
      digitalWrite(SENSE_PIN, HIGH); // call setSound()
    }
  }
  digitalWrite(SENSE_PIN, LOW);      //   stand-by call getSound()

  for ( i = 0; i < Repeats ; i++) {
    // if you want code size minimum, merge "digitalWrite(SENSE_PIN, LOW);" to here
    sw = Serial.read();              // key input check
    if ((sw != -1) ) {               // if detecting new inout
      digitalWrite(SENSE_PIN, HIGH); //   call setSound()
      i = 0;                         //   reset counter for new tone
    }                                // 
    digitalWrite(SENSE_PIN, LOW);    //   stand-by call getSound()
 
    // make square wave
    digitalWrite(SOUND_PIN, HIGH);
    delayMicroseconds(tmpNoteHIGH);
    digitalWrite(SOUND_PIN, LOW);
    delayMicroseconds(tmpNoteLOW);
  }
  Repeats = 0;                       // reset duration (for sound off)
}
//EOF
