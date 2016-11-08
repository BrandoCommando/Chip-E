#include "LCD_Display.h"

LiquidCrystal_I2C myLCD(0x27, 16, 2); //2x16 LCD control @ address 0x27

//--Custom characters for LCD display
const uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
const uint8_t char_block[8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };

//--Heart pattern variables
bool displayHeartsInverse = false;

//--Cylon effect variables
int cylonPosition = 0;
bool cylonDirection = true;

//--Eye position variables
int lastEyesPosition = EYES_CENTER;

void drawCylon()
{
  if ( cylonDirection )
  {
    if ( ++cylonPosition == 16 )
    {
      cylonPosition = 14;
      cylonDirection = false;
    }
  }
  else
  {
    if ( --cylonPosition == -1 )
    {
      cylonPosition = 1;
      cylonDirection = true;
    }
  }

  myLCD.clear();
  if ( cylonDirection )
  {
    myLCD.setCursor(cylonPosition - 1, 0);
    myLCD.write(1); //block
    myLCD.setCursor(cylonPosition - 1, 1);
    myLCD.write(1); //block
  }
  else
  {
    myLCD.setCursor(cylonPosition + 1, 0);
    myLCD.write(1); //block
    myLCD.setCursor(cylonPosition + 1, 1);
    myLCD.write(1); //block
  }
  myLCD.setCursor(cylonPosition, 0);
  myLCD.write(1); //block
  myLCD.setCursor(cylonPosition, 1);
  myLCD.write(1); //block
}

void drawEyes( int eyePosition )
{
  myLCD.clear();
  switch( eyePosition )
  {
  case EYES_LEFT:
    myLCD.setCursor(4, 0);
    myLCD.write(1); //block
    myLCD.setCursor(4, 1);
    myLCD.write(1); //block
    myLCD.setCursor(13, 0);
    myLCD.write(1); //block
    myLCD.setCursor(13, 1);
    myLCD.write(1); //block
    break;
  case EYES_CENTER:
    myLCD.setCursor(3, 0);
    myLCD.write(1); //block
    myLCD.setCursor(3, 1);
    myLCD.write(1); //block
    myLCD.setCursor(12, 0);
    myLCD.write(1); //block
    myLCD.setCursor(12, 1);
    myLCD.write(1); //block
    break;
  case EYES_RIGHT:
    myLCD.setCursor(2, 0);
    myLCD.write(1); //block
    myLCD.setCursor(2, 1);
    myLCD.write(1); //block
    myLCD.setCursor(11, 0);
    myLCD.write(1); //block
    myLCD.setCursor(11, 1);
    myLCD.write(1); //block
    break;
  case EYES_UP:
    myLCD.setCursor(3, 0);
    myLCD.write(1); //block
    myLCD.setCursor(12, 0);
    myLCD.write(1); //block
    break;
  case EYES_DOWN:
    myLCD.setCursor(3, 1);
    myLCD.write(1); //block
    myLCD.setCursor(12, 1);
    myLCD.write(1); //block
    break;
  case EYES_BLINK:
    delay(100); //lcd is clear so we pause for just a moment to blink
    drawEyes( lastEyesPosition );
    return; //returning because we do not need to store blink as the last position
  default:
    break;
  }

  lastEyesPosition = eyePosition;
}

void drawHearts()
{
  myLCD.clear();
  for ( int i = 0; i < 15; i += 2 )
  {
    if ( displayHeartsInverse ) myLCD.setCursor(i, 1);
    else myLCD.setCursor(i, 0);
    myLCD.write(0); //heart

    if ( displayHeartsInverse ) myLCD.setCursor(i + 1, 0);
    else myLCD.setCursor(i + 1, 1);
    myLCD.write(0); //heart
  }

  displayHeartsInverse = !displayHeartsInverse;
}
