
byte incoming = 0;
boolean on = 0;


void setup() {

  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);

}

void loop() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  delay(1000);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
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

