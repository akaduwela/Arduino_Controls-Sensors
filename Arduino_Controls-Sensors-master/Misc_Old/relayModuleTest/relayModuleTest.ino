
byte incoming = 0;
boolean on = 0;


void setup() {

  Serial.begin(9600);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);

}

void loop() {
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  delay(1000);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  delay(1000);

}



//if (Serial.available() > 0) {
//    incoming = Serial.read();
//    if (incoming == 32) { //only toggles is space is sent
//      on = !on;
//      Serial.println(on);
//
//
//        digitalWrite(5, on);
//    }
//  }



//Serial.println("dick");
//digitalWrite(5,HIGH);
//delay(1000);
//digitalWrite(5,LOW);
//delay(1000);

