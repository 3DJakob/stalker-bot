typedef enum DriveStates {
  Init,
  Stop,
  Frwd,
  Bkwd
};

DriveStates DState, LastDState;

byte RedLed = 11;
byte YellowLed = 10;
byte GreenLed = 9;

int motorSpeed = 0;
int lastMotorSpeed = 0;
int step = 5;

byte DistanceSensorInput = 1;
int DistanceSensorValue;

byte Pwm_b = 3;
byte Dir_b1 = 1;
byte Dir_b2 = 0;

void setup() {
  DState = Init;
  LastDState = Init;

  pinMode(RedLed, OUTPUT);
  pinMode(YellowLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);

  pinMode(Pwm_b, OUTPUT);
  pinMode(Dir_b1, OUTPUT);
  pinMode(Dir_b2, OUTPUT);

  analogWrite(Pwm_b, 0);

  Serial.begin(9600);
}

void loop() {
  DistanceSensorValue = analogRead(DistanceSensorInput);
  DistanceSensorValue = analogRead(5);

  Serial.println(motorSpeed);

  switch (DState) {
    case Init:
      digitalWrite(YellowLed, LOW);
      digitalWrite(GreenLed, LOW);
      digitalWrite(RedLed, HIGH);
      delay(1000);
      Serial.println("starting");
      DState = Stop;
    break;

    case Stop:
      digitalWrite(YellowLed, HIGH);
      digitalWrite(GreenLed, LOW);
      digitalWrite(RedLed, LOW);
      motorRun(0);
      if (DistanceSensorValue < 170) {
        DState = Frwd;
      } else if (DistanceSensorValue > 230) {
        DState = Bkwd;
      }
    break;

    case Frwd:
      digitalWrite(YellowLed, LOW);
      digitalWrite(GreenLed, HIGH);
      digitalWrite(RedLed, LOW);
      motorRun(1);
      if (DistanceSensorValue > 170) {
        DState = Stop;
      }
    break;

    case Bkwd:
      digitalWrite(YellowLed, LOW);
      digitalWrite(GreenLed, LOW);
      digitalWrite(RedLed, HIGH);
      motorRun(2);
      if (DistanceSensorValue < 230) {
        DState = Stop;
      }
    break;
  }
}
