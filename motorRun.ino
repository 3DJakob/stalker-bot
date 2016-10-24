void motorRun (int direction) {
  if (direction) {
    digitalWrite(Dir_b1, HIGH);
    digitalWrite(Dir_b2, LOW);

  } else {
    digitalWrite(Dir_b1, HIGH);
    digitalWrite(Dir_b2, LOW);
  }

  if (motorSpeed < 256){
    motorSpeed = lastMotorSpeed +1;
    analogWrite(Pwm_b, motorSpeed);
    lastMotorSpeed = motorSpeed;
  }
}
