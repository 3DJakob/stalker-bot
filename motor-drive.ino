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
int lastMotorSpeed;

byte DistanceSensorInput = 1;
int DistanceSensorValue;
byte LastSpeed = 0;
//byte DistSpeed = DistanceSensorValue*-1+170;
int MotorSpeedFrwd = map(DistanceSensorValue, 0, 170, 100, 0);

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

  analogWrite(Pwm_b, 0); //Problem with |?

  Serial.begin(9600);
}

void loop() {
  DistanceSensorValue = analogRead(DistanceSensorInput);
  DistanceSensorValue = analogRead(0);
  //Serial.println(DState);
  //Serial.println(DistanceSensorValue);
  Serial.print("motorSpeed:");
  Serial.println(motorSpeed);

  switch (DState) {
    case Init:
      digitalWrite(YellowLed, LOW);
      digitalWrite(GreenLed, LOW);
      digitalWrite(RedLed, HIGH);
      delay(5000);
      Serial.println("starting");
      DState = Stop;
    break;

    case Stop:
      digitalWrite(YellowLed, HIGH);
      digitalWrite(GreenLed, LOW);
      digitalWrite(RedLed, LOW);

      motorSpeed = 0;
      lastMotorSpeed = 0;
      //Motor_1(0,10); // Not defined?
      //delay(100);
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

      //Motor_1(100,10);
      //delay(50);
      if (DistanceSensorValue > 170) {
        DState = Stop;
      }
    break;

    case Bkwd:
      digitalWrite(YellowLed, LOW);
      digitalWrite(GreenLed, LOW);
      digitalWrite(RedLed, HIGH);

      motorRun(0);

      //Motor_1(100,10);
      //delay(50);
      if (DistanceSensorValue < 230) {
        DState = Stop;
      }
    break;
  }
}
