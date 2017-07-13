/***********************************************************************************
 *  Wiring
 *
 *    LEDs - Digital Pin 4
 *    Left Hip Servo - Digital Pin 10
 *    Right Hip Servo - Digital Pin 9
 *    Left Ankle Servo - Digital Pin 6
 *    Right Ankle Servo - Digital Pin 5
 *    Left Arm Servo - Digital Pin 12
 *    Right Arm Servo - Digital Pin 13
 *
 *  Control Behavior:
 *
 *    Power on Chip-E for a short demonstration.
 *
 ***********************************************************************************/

#define NUMPIXELS      16
#define PIN_RR 6 //Roll Right
#define PIN_RL 3 //Roll Left
#define PIN_YR 5 //Yaw Right
#define PIN_YL 9 //Yaw Left
#define PIN_AL 10 //Arm Left
#define PIN_AR 11 //Arm Right
//#define PIN_EYES 13 //LED for Eyes

#include <ChipE.h>
#if defined(PIN_EYES)
  #include <Adafruit_NeoPixel.h>
  #ifdef __AVR__
    #include <avr/power.h>
  #endif
#endif
const int TRIM_RR = -20; //Trim on the right ankle (adjust +/- as necessary)
const int TRIM_RL = -40; //Trim on the left ankle (adjust +/- as necessary)
const int TRIM_YR = -25; //Trim on the right hip (adjust +/- as necessary)
const int TRIM_YL = 15; //Trim on the left hip (adjust +/- as necessary)


enum EYE_POSITIONS
{
  EYES_LEFT,
  EYES_CENTER,
  EYES_RIGHT,
  EYES_UP,
  EYES_DOWN,
  EYES_BLINK
};

const uint8_t pixel_offsets[5] = { 0, 7, 4, 2, 6 };
int lastEyesPosition = EYES_CENTER;

ChipE myChipE; //Chip-E object (your robot!:)
#if defined(PIN_EYES)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_EYES, NEO_GRB + NEO_KHZ800);
#endif

void setup()
{
  Serial.begin(38400);

  //--LCD initialization
  #if defined(PIN_EYES)
  pixels.begin();
  #endif
  drawEyes( EYES_CENTER );

  //--Chip-E initialization
  myChipE.init( PIN_YL, PIN_YR, PIN_RL, PIN_RR );
  myChipE.setTrims( TRIM_YL, TRIM_YR, TRIM_RL, TRIM_RR ); //Set the servo trims
  myChipE.home(); //Move feet to home position
  delay( 500 );

  //--Sound initialization
}

void loop()
{
  drawEyes( EYES_CENTER );
  myChipE.home();
  delay( 500 );

  drawEyes( EYES_DOWN );
  myChipE.walk( 4, 2000, FORWARD );
  drawEyes( EYES_CENTER );
  myChipE.walk( 4, 1000, FORWARD );

  myChipE.home();

  drawEyes( EYES_UP );
  myChipE.walk( 4, 1000, BACKWARD );
  drawEyes( EYES_CENTER );
  myChipE.walk( 4, 2000, BACKWARD );

  myChipE.home();

  drawEyes( EYES_RIGHT );
  myChipE.turn( 3, 2000, RIGHT );
  drawEyes( EYES_LEFT );
  myChipE.turn( 3, 2000, LEFT );

  drawEyes( EYES_UP );
  myChipE.updown( 6, 500, SMALL );
  myChipE.updown( 6, 500, MEDIUM );
  drawEyes( EYES_DOWN );
  myChipE.updown( 2, 4000, BIG );

  drawEyes( EYES_LEFT );
  myChipE.moonwalker( 3, 2000, 30, LEFT );
  drawEyes( EYES_RIGHT );
  myChipE.moonwalker( 3, 2000, 30, RIGHT );

  drawEyes( EYES_CENTER );
  myChipE.swing( 6, 600, 10 );
  myChipE.swing( 4, 2000, 40 );

  drawEyes( EYES_LEFT );
  myChipE.crusaito( 6, 2000, 40, LEFT );
  drawEyes( EYES_RIGHT );
  myChipE.crusaito( 6, 2000, 40, RIGHT );

  drawEyes( EYES_DOWN );
  myChipE.flapping( 10, 600, 10, FORWARD );
  drawEyes( EYES_UP );
  myChipE.flapping( 10, 600, 10, BACKWARD );

}

void clearEyes()
{
  #if defined(PIN_EYES)
  for(int i=0;i<NUMPIXELS;i++)
    pixels.setPixelColor(i, 0);
  #endif
}

void drawEyes( int eyePosition )
{
  #if defined(PIN_EYES)
  switch( eyePosition )
  {
  case EYES_LEFT:
  case EYES_CENTER:
  case EYES_RIGHT:
  case EYES_UP:
  case EYES_DOWN:
    clearEyes();
    pixels.setPixelColor(pixel_offsets[eyePosition], pixels.Color(0,150,0));
    pixels.setPixelColor(floor(NUMPIXELS/2)+pixel_offsets[eyePosition], pixels.Color(0,150,0));
    pixels.show();
    break;
  case EYES_BLINK:
    clearEyes();
    pixels.show();
    delay(100); //lcd is clear so we pause for just a moment to blink
    drawEyes( lastEyesPosition );
    return; //returning because we do not need to store blink as the last position
  default:
    break;
  }

  lastEyesPosition = eyePosition;
  #endif
}

