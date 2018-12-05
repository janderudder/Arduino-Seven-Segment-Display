/**
 * SevenSegmentDisplay.cpp
 * Author: Jan Derudder
 * 
 * Seven segment display driver class.
 * Implementation.
 */
#include "SevenSegmentDisplay.hpp"
#include <Arduino.h>
#include <assert.h>

/** 
 * Static member init.
 * Displayables values encoded as bytes
 * bit <-> segment name = 0bABCDEFGP
 */
const uint8_t SevenSegmentDisplay::mPredefValues[] = {
  0b11111100,   // Val_0
  0b01100000,   // Val_1
  0b11011010,   // ...
  0b11110010,
  0b01100110,
  0b10110110,   // Val_5
  0b10111110,
  0b11100000,
  0b11111110,
  0b11110110,
  0b11101110,   // Val_A
  0b00111110,
  0b10011100,
  0b01111010,
  0b10011110,
  0b10001110,   // Val_F
  0b00000010,   // Val_MINUS
  0b00000000    // Val_Clear
};


/**
 * Constructor
 */
SevenSegmentDisplay::SevenSegmentDisplay(ComponentType type)
  : mOnLevel  { type == COMCATHODE ? HIGH : LOW  }
  , mOffLevel { type == COMCATHODE ? LOW  : HIGH }
{
  // Verify we passed one of the two valid values
  assert(type == COMCATHODE || type == COMANODE);
}



void SevenSegmentDisplay::initPin(Seg seg, pin_t pin)
{
  // Save the arduino <−> display pins correspondance.
  mPins[seg] = pin;
  
  // Set the arduino pin as output.
  pinMode(pin, OUTPUT);
}



void SevenSegmentDisplay::clear()
{
  for (int i=0; i < 8; i++)
    digitalWrite(mPins[i], mOffLevel);
}



void SevenSegmentDisplay::display(Predef value)
{
  this->setLevels(mPredefValues[static_cast<int>(value)]);
  this->writeLevels();
}



void SevenSegmentDisplay::display(Point pointState)
{
  this->setSegment(
    SEG_P,
    pointState == Point::Off ? State::Off : State::On
  );
}



void SevenSegmentDisplay::display(int valueIndex)
{
  this->setLevels(mUsedValues[valueIndex]);
  this->writeLevels();
}



void SevenSegmentDisplay::usePredefinedValues()
{
  this->mUsedValues = SevenSegmentDisplay::mPredefValues;
}



void SevenSegmentDisplay::useCustomValues(const uint8_t* values)
{
  this->mUsedValues = values;
}



void SevenSegmentDisplay::setSegment(Seg seg, State state)
{
  digitalWrite(mPins[seg], this->stateToLevel(state));
}



int SevenSegmentDisplay::maxPredefinedValue()
{
  return static_cast<int>(Predef::Val_Clear) - 1;
}



bool SevenSegmentDisplay::isValidPredefined(int value)
{
  return value <= this->maxPredefinedValue() && value >= 0 ?
    true : false;
}



//////////////////////////////////////////////////
// Private methods
//////////////////////////////////////////////////
int SevenSegmentDisplay::stateToLevel(State state) const
{
  return state == State::Off ?
    this->mOffLevel:
    this->mOnLevel;
}


void SevenSegmentDisplay::setLevels(const uint8_t levels)
{
  for (int i=0; i < 7; ++i)
    mSegmentLevel[i] = ((levels << i) & 0b10000000) ?
      &mOnLevel : &mOffLevel;
}


void SevenSegmentDisplay::writeLevels()
{
  for (int i=0; i < 8; ++i)
    digitalWrite(mPins[i], *mSegmentLevel[i]);
}
