void motorRun (int direction) {
  if (direction == 1) {
    if (motorSpeed < 255){
      motorSpeed = lastMotorSpeed + step;
    }
  } else if (direction == 2) {
    if (motorSpeed > -255){
      motorSpeed = lastMotorSpeed - step;
    }
  } else {
    if (motorSpeed > 0){
      motorSpeed = lastMotorSpeed - step;
    } else if (motorSpeed < 0) {
      motorSpeed = lastMotorSpeed + step;
    }
  }

  if (motorSpeed > 0) {
    digitalWrite(Dir_b1, HIGH);
    digitalWrite(Dir_b2, LOW);
    analogWrite(Pwm_b, motorSpeed);
  } else {
    digitalWrite(Dir_b1, LOW);
    digitalWrite(Dir_b2, HIGH);
    analogWrite(Pwm_b, -motorSpeed);
  }
  lastMotorSpeed = motorSpeed;
}
