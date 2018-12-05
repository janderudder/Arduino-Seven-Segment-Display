/**
 * SevenSegmentDisplay.hpp
 * Author: Jan Derudder
 * 
 * Seven segment display driver class.
 * 
 */
#ifndef SEVENSEGMENTDISPLAY_HPP
#define SEVENSEGMENTDISPLAY_HPP
#include <stdint.h>

class SevenSegmentDisplay
{
  // Display <-> Arduino pin map
  int mPins[8] = {
    -1, -1, -1, -1,
    -1, -1, -1, -1
  };

  // Appropriate logic level according to
  // display component type.
  const int mOnLevel;
  const int mOffLevel;

  // Store for predefined displayable values 
  // encoded on bytes
  static const uint8_t mPredefValues[];

  // For each segment, the current
  // logical level
  const int* mSegmentLevel[8] = {
    &mOffLevel, &mOffLevel,
    &mOffLevel, &mOffLevel,
    &mOffLevel, &mOffLevel,
    &mOffLevel, &mOffLevel
  };

  const uint8_t* mUsedValues = mPredefValues;
  
  using pin_t = int;
 
public:
  // Type of component
  enum ComponentType : char {
    COMANODE, COMCATHODE
  };

  // Component's segments names
  enum Seg : int {
    SEG_A, SEG_B, SEG_C, 
    SEG_D, SEG_E, SEG_F,
    SEG_G, SEG_P
  };

  // Predefined displayable alphanumeric
  // values, integer index to find them
  // in the corresponding array.
  enum class Predef : int {
    Val_0, Val_1, Val_2, Val_3,
    Val_4, Val_5, Val_6, Val_7,
    Val_8, Val_9, Val_A, Val_b,
    Val_B =Val_b, Val_C, Val_d,
    Val_D =Val_d, Val_E, Val_F,
    Val_MINUS,    Val_Clear
  };

  // Control the point state
  enum class Point : uint8_t {
    Off, On
  };

  // Logical states of a segment
  enum State : char {
    Off, On
  };

  /**
   * Constructor.
   * @argument SevenSegmentDisplay::ComponentType 
   *           Common anode or Common cathode.
   */
  explicit SevenSegmentDisplay(ComponentType);

  
  void initPin(Seg, pin_t);

  
  void clear();

  
  void display(Predef);
  void display(Point);
  void display(int);

  void usePredefinedValues();
  void useCustomValues(const uint8_t*);

  
  void setSegment(Seg, State);

  
  int maxPredefinedValue();

  
  bool isValidPredefined(int);


private: /* Private methods */
  int stateToLevel(State) const;
  void setLevels(const uint8_t);
  void writeLevels();
  
};

#endif // SEVENSEGMENTDISPLAY_HPP
