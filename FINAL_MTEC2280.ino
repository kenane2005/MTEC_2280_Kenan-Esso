/*
Kenan Esso
Final Project - BEAT MACHINE

2 Potentiometers + 8 Buttons + LED
Arduino to Max/MSP

Pot 1 = Master Volume
Pot 2 = Filter Frequency
Buttons 1-4 = Chords
Buttons 5-8 = Drums
*/

#define adcPin_1 1
#define adcPin_2 2

#define buttonPin_1 19
#define buttonPin_2 20
#define buttonPin_3 21
#define buttonPin_4 47
#define buttonPin_5 46
#define buttonPin_6 45
#define buttonPin_7 35
#define buttonPin_8 36

#define ledPin 4

int adcRead_1 = 0;
int adcRead_2 = 0;
int inByte = 0;

int lastTime = 0;
int currentTime = 0;
int timerInterval = 50;

// remembers previous button states
int lastButtonState_1 = 0;
int lastButtonState_2 = 0;
int lastButtonState_3 = 0;
int lastButtonState_4 = 0;
int lastButtonState_5 = 0;
int lastButtonState_6 = 0;
int lastButtonState_7 = 0;
int lastButtonState_8 = 0;

void setup() {
  pinMode(buttonPin_1, INPUT_PULLUP);
  pinMode(buttonPin_2, INPUT_PULLUP);
  pinMode(buttonPin_3, INPUT_PULLUP);
  pinMode(buttonPin_4, INPUT_PULLUP);
  pinMode(buttonPin_5, INPUT_PULLUP);
  pinMode(buttonPin_6, INPUT_PULLUP);
  pinMode(buttonPin_7, INPUT_PULLUP);
  pinMode(buttonPin_8, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  analogReadResolution(12);
  Serial.begin(9600);
}

void loop() {

  // Receive start/stop message from Max
  if (Serial.available()) {
    inByte = Serial.read();
  }

  currentTime = millis();

  if (currentTime - lastTime >= timerInterval) {
    lastTime = currentTime;

    // only send data when Max sends 255
    if (inByte == 255) {

      // read potentiometers
      adcRead_1 = analogRead(adcPin_1);
      adcRead_2 = analogRead(adcPin_2);

      // read buttons
      int buttonState_1 = !digitalRead(buttonPin_1);
      int buttonState_2 = !digitalRead(buttonPin_2);
      int buttonState_3 = !digitalRead(buttonPin_3);
      int buttonState_4 = !digitalRead(buttonPin_4);
      int buttonState_5 = !digitalRead(buttonPin_5);
      int buttonState_6 = !digitalRead(buttonPin_6);
      int buttonState_7 = !digitalRead(buttonPin_7);
      int buttonState_8 = !digitalRead(buttonPin_8);

      // one-shot trigger: only sends 1 once when newly pressed
      int trigger_1 = buttonState_1 && !lastButtonState_1;
      int trigger_2 = buttonState_2 && !lastButtonState_2;
      int trigger_3 = buttonState_3 && !lastButtonState_3;
      int trigger_4 = buttonState_4 && !lastButtonState_4;
      int trigger_5 = buttonState_5 && !lastButtonState_5;
      int trigger_6 = buttonState_6 && !lastButtonState_6;
      int trigger_7 = buttonState_7 && !lastButtonState_7;
      int trigger_8 = buttonState_8 && !lastButtonState_8;

      // update last states
      lastButtonState_1 = buttonState_1;
      lastButtonState_2 = buttonState_2;
      lastButtonState_3 = buttonState_3;
      lastButtonState_4 = buttonState_4;
      lastButtonState_5 = buttonState_5;
      lastButtonState_6 = buttonState_6;
      lastButtonState_7 = buttonState_7;
      lastButtonState_8 = buttonState_8;

      // LED turns on while any button is held
      if (buttonState_1 || buttonState_2 || buttonState_3 || buttonState_4 ||
          buttonState_5 || buttonState_6 || buttonState_7 || buttonState_8) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }

      // send to Max:
      // pot1 pot2 button1 button2 button3 button4 button5 button6 button7 button8
      Serial.print(adcRead_1);
      Serial.print(' ');
      Serial.print(adcRead_2);
      Serial.print(' ');
      Serial.print(trigger_1);
      Serial.print(' ');
      Serial.print(trigger_2);
      Serial.print(' ');
      Serial.print(trigger_3);
      Serial.print(' ');
      Serial.print(trigger_4);
      Serial.print(' ');
      Serial.print(trigger_5);
      Serial.print(' ');
      Serial.print(trigger_6);
      Serial.print(' ');
      Serial.print(trigger_7);
      Serial.print(' ');
      Serial.println(trigger_8);
    }

    else {
      digitalWrite(ledPin, LOW);
    }
  }
}