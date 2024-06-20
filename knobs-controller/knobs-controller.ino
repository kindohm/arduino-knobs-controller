#include <MIDIUSB.h>

int analogValues[6];

const int potentiometerPin = A0;  // Analog input pin for the potentiometer

const uint8_t midiChannel = 1;

void setup() {
  // Serial.begin(9600); 

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
    
    sendControlChange(midiChannel, index + 1, midiValue);

    // Serial.println(index);
    // Serial.println(midiValue);
  }
}

void loop() {

  readAnalogValue(A0, 0);
  readAnalogValue(A1, 1);
  readAnalogValue(A2, 2);
  readAnalogValue(A3, 3);
  readAnalogValue(A4, 4);
  readAnalogValue(A5, 5);

  // Small delay to avoid flooding MIDI messages
  delay(10);
}

void sendControlChange(uint8_t channel, uint8_t control, uint8_t value) {
  midiEventPacket_t event = {0x0B, 0xB0 | (channel - 1), control, value};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}


