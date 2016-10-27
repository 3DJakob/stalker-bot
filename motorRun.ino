// Motor run function!
// This motor function steps the motorSpeed in to the desired value i.e. stop, forward, backward.
// It uses a value between -255 & 255 to declare how fast and wich direction it's going.

void motorRun (int direction) { // Declare direction value ( 0=stop 1=forward 2=backward)
  if (direction == 1) { // If motor direction is forward
    if (motorSpeed < 255){
      motorSpeed = lastMotorSpeed + step; // If motor is not 255 speed increase speed
    }
  } else if (direction == 2) {  // If motor direction is backward
    if (motorSpeed > -255){
      motorSpeed = lastMotorSpeed - step; // If motor is not -255 speed decrease speed
    }
  } else { // motor direction is stop
    if (motorSpeed > 0){
      motorSpeed = lastMotorSpeed - step; // If motorSpeed is positive decrease
    } else if (motorSpeed < 0) {
      motorSpeed = lastMotorSpeed + step; // If motorSpeed is negative increase
    }
  }

  if (motorSpeed > 0) { // If motorSpeed is positive run motor forward
    digitalWrite(Dir_b1, HIGH);
    digitalWrite(Dir_b2, LOW);
    analogWrite(Pwm_b, motorSpeed); // Run the motor at motorSpeed
  } else {  // If motorSpeed is negative run motor backward
    digitalWrite(Dir_b1, LOW);
    digitalWrite(Dir_b2, HIGH);
    analogWrite(Pwm_b, -motorSpeed); // Run the motor at motorSpeed
  }
  lastMotorSpeed = motorSpeed;  // Set the lastMotorSpeed to the current
}
