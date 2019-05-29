/**
 * Usage example for the SevenSegmentDisplay class.
 */
#include "SevenSegmentDisplay.hpp"

// Time
unsigned long timer = 0;
short counter = 0;

// Alias to shorten class' name.
using SevSeg = SevenSegmentDisplay;

// Instance creation.
SevSeg sevSeg(SevSeg::COMCATHODE);


void setup() {
  // Mapping display pins to Arduino pins
  sevSeg.initPin(SevSeg::SEG_A, 7);
  sevSeg.initPin(SevSeg::SEG_B, 8);
  sevSeg.initPin(SevSeg::SEG_C, 6);
  sevSeg.initPin(SevSeg::SEG_D, 4);
  sevSeg.initPin(SevSeg::SEG_E, 2);
  sevSeg.initPin(SevSeg::SEG_F, 5);
  sevSeg.initPin(SevSeg::SEG_G, 3);
  sevSeg.initPin(SevSeg::SEG_P, 9);

  // Display init.
  sevSeg.clear();
 
}


void loop() {
  if (millis() - timer > 800) {
    timer = millis();
    counter++;

    if (counter > sevSeg.maxPredefinedValue())
      counter = 0;

    sevSeg.display(counter);
  }
}
