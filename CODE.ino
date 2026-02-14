// Flame sensor pins
int leftSensor = A0;
int centerSensor = A1;
int rightSensor = A2;

// Motor pins
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;

// Pump relay
int pump = 7;

// Threshold (adjust after testing)
int threshold = 500;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(pump, OUTPUT);

  Serial.begin(9600);
}

// Motor functions
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  int leftVal = analogRead(leftSensor);
  int centerVal = analogRead(centerSensor);
  int rightVal = analogRead(rightSensor);

  Serial.print(leftVal); Serial.print(" ");
  Serial.print(centerVal); Serial.print(" ");
  Serial.println(rightVal);

  if (centerVal < threshold) {
    // Fire ahead
    forward();
    digitalWrite(pump, HIGH); // Pump ON
  }
  else if (leftVal < threshold) {
    left();
    digitalWrite(pump, LOW);
  }
  else if (rightVal < threshold) {
    right();
    digitalWrite(pump, LOW);
  }
  else {
    stopMotors();
    digitalWrite(pump, LOW);
  }

  delay(200);
}
