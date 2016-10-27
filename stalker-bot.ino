typedef enum DriveStates { // Defining possible DState values
  Init,
  Stop,
  Frwd,
  Bkwd
};

DriveStates DState; // Assigning possible DState values

// LED pins
byte RedLed = 11;
byte YellowLed = 10;
byte GreenLed = 9;

int motorSpeed = 0; // Current motor speed variable
int lastMotorSpeed = 0; // The last motor speed
int step = 5; // The motor speed derivative

byte DistanceSensorInput = 5; // Sensor input
int DistanceSensorValue;  // Sensor value 0 - 1023

byte Pwm_b = 3; // Motor pwm output
byte Dir_b1 = 1;  // Direction 1 pin
byte Dir_b2 = 0;  // Direction 2 pin

void setup() {
  DState = Init;  // Set the DState to init

  // Configure inputs/outputs
  pinMode(RedLed, OUTPUT);
  pinMode(YellowLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);

  pinMode(Pwm_b, OUTPUT);
  pinMode(Dir_b1, OUTPUT);
  pinMode(Dir_b2, OUTPUT);

  analogWrite(Pwm_b, 0); // Run motor at 0 speed
  Serial.begin(9600); // Begin serial monitor at 9600 baud rate
}

void loop() {
  DistanceSensorValue = analogRead(DistanceSensorInput);  // Read sensor

  Serial.println(motorSpeed); // Log motorSpeed

  switch (DState) { // State selected by DState variable
    case Init:  // If DState = Init => Turn on RedLed and wait 1s
      digitalWrite(YellowLed, LOW);
      digitalWrite(GreenLed, LOW);
      digitalWrite(RedLed, HIGH);
      delay(1000);
      Serial.println("starting");
      DState = Stop;
    break;  // End of case

    case Stop:  // If DState = Stop => Turn on YellowLed and run motor function
      digitalWrite(YellowLed, HIGH);
      digitalWrite(GreenLed, LOW);
      digitalWrite(RedLed, LOW);
      motorRun(0); // Run motor function, send value 0
      if (DistanceSensorValue < 170) {
        DState = Frwd;  // If DistanceSensorValue < 170 change DState to Frwd
      } else if (DistanceSensorValue > 230) {
        DState = Bkwd;  // If DistanceSensorValue > 230 change DState to Bkwd
      }
    break;  // End of case

    case Frwd:  // If DState = Frwd => Turn on GreenLed and run motor function
      digitalWrite(YellowLed, LOW);
      digitalWrite(GreenLed, HIGH);
      digitalWrite(RedLed, LOW);
      motorRun(1);  // Run motor function, send value 1
      if (DistanceSensorValue > 170) {
        DState = Stop;  // If DistanceSensorValue > 170 change DState to Stop
      }
    break;  // End of case

    case Bkwd:  // If DState = Bkwd => Turn on RedLed and run motor function
      digitalWrite(YellowLed, LOW);
      digitalWrite(GreenLed, LOW);
      digitalWrite(RedLed, HIGH);
      motorRun(2);  // Run motor function, send value 2
      if (DistanceSensorValue < 230) {
        DState = Stop;  // If DistanceSensorValue < 230 change DState to Stop
      }
    break;  // End of case
  }
}
