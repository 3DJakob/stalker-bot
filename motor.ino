void Motor_1(byte NewSpeed, long Step) {
  if (DState != LastDState) {
    NewSpeed = map(NewSpeed,0,100,0,255);
    LastDState = DState;

    switch (DState) {
      case Init:
      break;

      case Stop:
        for(byte Speed = LastSpeed+1 ; Speed <= NewSpeed; Speed -= 1) {
          analogWrite(Pwm_b, Speed);
          delay(Step);
        }

      break;

      case Frwd:
        digitalWrite(Dir_b1, HIGH);
        digitalWrite(Dir_b2, LOW);

        for(short Speed = LastSpeed; Speed <= NewSpeed; Speed += 1) {
          analogWrite(Pwm_b, Speed);
          delay(Step);
        }

        // for(short Speed = 0; Speed < NewSpeed; Speed++) {
        //   analogWrite(Pwm_b, Speed);
        //   delay(Step);
        // }
        // while (DState == Frwd) {
        //   analogWrite(Pwm_b, DistanceSensorValue*-1+170);
        //   Serial.println("looped!");
        // }


        // for(DState == Frwd) {
        //   byte DistSpeed = DistanceSensorValue*-1+170;
        //   analogWrite(Pwm_b, DistSpeed);
        //   //delay(Step);
        // }




      break;

      case Bkwd:
        digitalWrite(Dir_b1, LOW);
        digitalWrite(Dir_b2, HIGH);

        for(short Speed = LastSpeed; Speed <= NewSpeed; Speed += 1) {
          analogWrite(Pwm_b, Speed);
          delay(Step);
        }

    }
  LastSpeed = NewSpeed;
  }
}
