#include <Joystick.h>

#define PADDLE1_PIN 2
#define PADDLE2_PIN 3

#define MODE_PADDLE 1
#define MODE_DRIVING 2
#define MODE_JOYSTICK 3
#define MODE_TOUCHPAD 4

uint8_t mode;
void setup() {
  Serial.begin(9600);
  mode = detectMode();

  switch(mode) {
    case MODE_PADDLE:
      pinMode(PADDLE2_PIN, OUTPUT);
      digitalWrite(PADDLE2_PIN, LOW);
      attachInterrupt(digitalPinToInterrupt(PADDLE2_PIN), setPaddle2Flag, RISING);
      pinMode(PADDLE2_PIN, INPUT);      

      pinMode(PADDLE1_PIN, OUTPUT);
      digitalWrite(PADDLE1_PIN, LOW);
      attachInterrupt(digitalPinToInterrupt(PADDLE1_PIN), setPaddle1Flag, RISING);
      pinMode(PADDLE1_PIN, INPUT);
    break;
  }
}

uint8_t detectMode() {
  return MODE_PADDLE;
}

unsigned long paddle1Timer = 0;
unsigned long paddle2Timer = 0;

volatile bool updatePaddle1 = false;
volatile bool updatePaddle2 = false;

void setPaddle1Flag() {
  updatePaddle1 = true;
}

void setPaddle2Flag() {
  updatePaddle2 = true;
}

unsigned long paddle1Value = 0;
unsigned long paddle2Value = 0;

uint8_t calcPaddleValue(unsigned long* lastTime, uint8_t paddlePin, void (*setFlag)(void)) {
  detachInterrupt(paddlePin);
    
  unsigned long now = micros();
  unsigned long newValue = now - *lastTime;

  Serial.print(paddle1Value, DEC);
  Serial.print(", ");
  Serial.println(paddle2Value, DEC);
  
  pinMode(paddlePin, OUTPUT);
  digitalWrite(paddlePin, LOW);
  attachInterrupt(digitalPinToInterrupt(paddlePin), setFlag, RISING);
  *lastTime = micros();
  pinMode(paddlePin, INPUT);
  
  return newValue;
}

void loop() {
  switch(mode) {
    case MODE_PADDLE:
      handlePaddles();
    break;
    case MODE_JOYSTICK:
      handleJoystick();
    break;
    case MODE_TOUCHPAD:
      handleTouchpad();
    break;
    case MODE_DRIVING:
      handleDriving();
    break;
  }
}

void handleJoystick() {
}

void handlePaddles() {
  if (updatePaddle1 == true) {
    updatePaddle1 = false;
    paddle1Value = calcPaddleValue(&paddle1Timer, PADDLE1_PIN, setPaddle1Flag);
  }
  if (updatePaddle2 == true) {
    updatePaddle2 = false;
    paddle2Value = calcPaddleValue(&paddle2Timer, PADDLE2_PIN, setPaddle2Flag);
  }
}

void handleDriving() {
}

void handleTouchpad() {
}

