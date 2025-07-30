// --- configuration x axis ---
#define STEP_PIN_X 4
#define DIR_PIN_X 13
#define ENA_PIN_X 2

// --- Limit Switches for x axis ---
#define LIMIT_SWITCH_PIN1 5
#define LIMIT_SWITCH_PIN2 6

bool currentDirectionX = LOW;
bool switch1PreviouslyPressed = false;
bool switch2PreviouslyPressed = false;

void setup() {
  
  pinMode(STEP_PIN_X, OUTPUT);
  pinMode(DIR_PIN_X, OUTPUT);
  pinMode(ENA_PIN_X, OUTPUT);
  digitalWrite(ENA_PIN_X, LOW);  // تفعيل الدرايفر
  digitalWrite(DIR_PIN_X, currentDirectionX); // اتجاه مبدئي

  //  limit switches
  pinMode(LIMIT_SWITCH_PIN1, INPUT_PULLUP);
  pinMode(LIMIT_SWITCH_PIN2, INPUT_PULLUP);
}

void loop() {
  //read switches
  bool switch1Pressed = (digitalRead(LIMIT_SWITCH_PIN1) == LOW);
  bool switch2Pressed = (digitalRead(LIMIT_SWITCH_PIN2) == LOW);

  // swap direction if switch is pressed 
  if (switch1Pressed && !switch1PreviouslyPressed) {
    currentDirectionX = !currentDirectionX;
    digitalWrite(DIR_PIN_X, currentDirectionX);
    delay(300);  //some delay
  }

  if (switch2Pressed && !switch2PreviouslyPressed) {
    currentDirectionX = !currentDirectionX;
    digitalWrite(DIR_PIN_X, currentDirectionX);
    delay(300);
  }

  // update status
  switch1PreviouslyPressed = switch1Pressed;
  switch2PreviouslyPressed = switch2Pressed;

  // pulse 
  digitalWrite(STEP_PIN_X, HIGH);
  delayMicroseconds(50);
  digitalWrite(STEP_PIN_X, LOW);
  delayMicroseconds(50);
}