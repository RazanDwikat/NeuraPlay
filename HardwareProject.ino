#define STEP_PIN   9
#define DIR_PIN_1  8
#define DIR_PIN_2  11

#define LIMIT_SWITCH_1 22
#define LIMIT_SWITCH_2 23

const unsigned long stepsPerRevolution = 1600UL;

bool dir1 = true;
bool dir2 = false;

void setup() {
  Serial.begin(9600);

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN_1, OUTPUT);
  pinMode(DIR_PIN_2, OUTPUT);

  pinMode(LIMIT_SWITCH_1, INPUT_PULLUP);
  pinMode(LIMIT_SWITCH_2, INPUT_PULLUP);
}

void stepBoth(unsigned long steps, unsigned int stepDelayUs) {
  digitalWrite(DIR_PIN_1, dir1 ? HIGH : LOW);
  digitalWrite(DIR_PIN_2, dir2 ? HIGH : LOW);

  for (unsigned long i = 0; i < steps; ++i) {
    if (digitalRead(LIMIT_SWITCH_1) == LOW || digitalRead(LIMIT_SWITCH_2) == LOW) {
      Serial.println("Limit switch pressed! Reversing directions");

      dir1 = !dir1;
      dir2 = !dir2;
      digitalWrite(DIR_PIN_1, dir1 ? HIGH : LOW);
      digitalWrite(DIR_PIN_2, dir2 ? HIGH : LOW);
      delay(200);  

      for (int j = 0; j < 20; j++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(stepDelayUs);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(stepDelayUs);
      }

      break;  
    }

    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(stepDelayUs);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(stepDelayUs);
  }
}

void loop() {
  Serial.println("Moving motors...");
  stepBoth(stepsPerRevolution, 1000);
  delay(100);
}
