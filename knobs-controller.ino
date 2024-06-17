#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int analogValues[6];

const int potentiometerPin = A0;  // Analog input pin for the potentiometer
const int midiChannel = 1;        // MIDI channel (1-16)
const int controllerNumber = 7;   // MIDI CC number (e.g., 7 for volume)

void setup() {
  // Initialize serial communication for MIDI output
  MIDI.begin(midiChannel);
  Serial.begin(9600);  // MIDI baud rate

  // Optionally, you can send an initial message
  // MIDI.sendControlChange(controllerNumber, 0, midiChannel);
  analogValues[0] = 0;
  analogValues[1] = 0;
  analogValues[2] = 0;
  analogValues[3] = 0;
  analogValues[4] = 0;
  analogValues[5] = 0;
}



int readAnalogValue(int pin, int index) {
  int potValue = analogRead(pin);
  int midiValue = map(potValue, 0, 1023, 0, 127);
  if (analogValues[index] != midiValue) {
    analogValues[index] = midiValue;
    MIDI.sendControlChange(controllerNumber, midiValue, midiChannel);
    Serial.println(index);
    Serial.println(midiValue);
  }
}

void loop() {

  readAnalogValue(A0, 0);
  readAnalogValue(A1, 1);
  // readAnalogValue(A2, 2);
  // readAnalogValue(A3, 3);
  // readAnalogValue(A4, 4);
  // readAnalogValue(A5, 5);

  // // Serial.println('hi');

  // // Read the potentiometer value (0-1023)
  // int potentiometerValue = analogRead(potentiometerPin);

  // // Map the potentiometer value to a MIDI CC value (0-127)
  // int midiValue = map(potentiometerValue, 0, 1023, 0, 127);

  // if (midiValue != analog1Value) {
  //   Serial.println(midiValue);

  //   // Send the MIDI Control Change message
  //   MIDI.sendControlChange(controllerNumber, midiValue, midiChannel);
  //   analog1Value = midiValue;
  // }


  // Small delay to avoid flooding MIDI messages
  delay(10);
}
