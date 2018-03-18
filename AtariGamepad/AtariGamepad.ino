#define PADDLE1_PIN 7
#define PADDLE2_PIN 3

volatile bool updatePaddle1 = false;
volatile bool updatePaddle2 = false;

void setPaddle1Flag() {
  updatePaddle1 = true;
}

void setPaddle2Flag() {
  updatePaddle2 = true;
}

void setup() {
  Serial.begin(9600);
  pinMode(PADDLE1_PIN, INPUT);
  pinMode(PADDLE2_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(PADDLE1_PIN), setPaddle1Flag, RISING);
  attachInterrupt(digitalPinToInterrupt(PADDLE2_PIN), setPaddle2Flag, RISING);
}

unsigned long paddle1Timer = 0;
unsigned long paddle2Timer = 0;

uint8_t calcPaddleValue(unsigned long* lastTime) {
  unsigned long now = micros();
  unsigned long newValue = now - *lastTime;
  *lastTime = now;
  return newValue;
}

unsigned long paddle1Value = 0;
unsigned long paddle2Value = 0;

void loop() {
  if (updatePaddle1 == true) {
    paddle1Value = calcPaddleValue(&paddle1Timer);
  }
  if (updatePaddle2 == true) {
    paddle2Value = calcPaddleValue(&paddle2Timer);
  }
  Serial.print(paddle1Value);
  Serial.print(" ");
  Serial.print(paddle2Value);
  Serial.println("");
}

