/*
  MAX7219 using the LedControl Library - displaying text
  Copyright 2023 Gary Hallberg
  Licensed under MIT Licensed under MIT https://github.com/ghallberg-nbtt/special-lamp/blob/main/LICENSE
*/
#include "LedControl.h"

// Define numbers on the dice face
const byte N1[] = { B00000000,
                    B00000000,
                    B00000000,
                    B00011000,
                    B00011000,
                    B00000000,
                    B00000000,
                    B00000000 };

const byte N2[] = { B11000000,
                    B11000000,
                    B00000000,
                    B00000000,
                    B00000000,
                    B00000000,
                    B00000011,
                    B00000011 };

const byte N3[] = { B11000000,
                    B11000000,
                    B00000000,
                    B00011000,
                    B00011000,
                    B00000000,
                    B00000011,
                    B00000011 };

const byte N4[] = { B11000011,
                    B11000011,
                    B00000000,
                    B00000000,
                    B00000000,
                    B00000000,
                    B11000011,
                    B11000011 };

const byte N5[] = { B11000011,
                    B11000011,
                    B00000000,
                    B00011000,
                    B00011000,
                    B00000000,
                    B11000011,
                    B11000011 };

const byte N6[] = { B11000011,
                    B11000011,
                    B00000000,
                    B11000011,
                    B11000011,
                    B00000000,
                    B11000011,
                    B11000011 };


const int BUTTON = 5;  //button to roll dice
const int LED = 13;    //OK to roll dice

LedControl lc = LedControl(2, 4, 3, 1);

int number;

void setup() {
  /*
    The MAX72XX is in power - saving mode on startup,
      we have to do a wakeup call.
      display 1 has an index of 0
  */
  lc.shutdown(0, false);
  // Set the brightness to a medium value
  lc.setIntensity(0, 8);
  // and clear the display
  lc.clearDisplay(0);

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);  //Ready to roll
}

void loop() {
  while (digitalRead(BUTTON) == HIGH) {}  // Wait for button press
  digitalWrite(LED, LOW);                 // LED off as roll in action
  rollDice();
  randomSeed(millis()); // Try to make sure we have a random number
  // Generate number
  number = random(1, 7);  // 7 will mean max number is 6 i.e. 1 to 6
  // show the number
  switch (number) {
    case 1:
      for (int i = 0; i < 8; i++) {
        lc.setRow(0, i, N1[i]);
      };
      break;
    case 2:
      for (int i = 0; i < 8; i++) {
        lc.setRow(0, i, N2[i]);
      }
      break;
    case 3:
      for (int i = 0; i < 8; i++) {
        lc.setRow(0, i, N3[i]);
      }
      break;
    case 4:
      for (int i = 0; i < 8; i++) {
        lc.setRow(0, i, N4[i]);
      }
      break;
    case 5:
      for (int i = 0; i < 8; i++) {
        lc.setRow(0, i, N5[i]);
      }
      break;
    case 6:
      for (int i = 0; i < 8; i++) {
        lc.setRow(0, i, N6[i]);
      }
      break;
  }
  // Add a delay before next roll
  delay(1500);
  digitalWrite(LED, HIGH);  // OK to roll again
}

void rollDice() {
  // Function to roll dice

  for (int i = 1; i < 5; i++) {
    // one
    for (int i = 0; i < 8; i++) {
      lc.setRow(0, i, N1[i]);
    }
    delay(80);
    // two
    for (int i = 0; i < 8; i++) {
      lc.setRow(0, i, N2[i]);
    }
    delay(80);
    for (int i = 0; i < 8; i++) {
      lc.setRow(0, i, N3[i]);
    }
    delay(80);
    for (int i = 0; i < 8; i++) {
      lc.setRow(0, i, N4[i]);
    }
    delay(80);
    for (int i = 0; i < 8; i++) {
      lc.setRow(0, i, N5[i]);
    }
    delay(80);
    for (int i = 0; i < 8; i++) {
      lc.setRow(0, i, N6[i]);
    }
    delay(80);
  }
}