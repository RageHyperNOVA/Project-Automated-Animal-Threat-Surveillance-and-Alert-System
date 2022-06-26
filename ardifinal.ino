#include<SoftwareSerial.h>
String incomingByte ;    
int buzzerPin = 8;
SoftwareSerial mySerial1 (2,3);
void setup() {
  mySerial1.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);
  delay(100);
  randomSeed(analogRead(0));
  pinMode(buzzerPin, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(11, HIGH);
  noTone(buzzerPin);
}
void loop() {

  if (Serial.available() > 0) {

  incomingByte = Serial.readStringUntil('\n');

    if (incomingByte == "on") {

      digitalWrite(13, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      tone(buzzerPin,2000);
      Serial.write("Led on");
      mySerial1.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);  // Delay of 1 second
      mySerial1.println("AT+CMGS=\"+919558207116\"\r"); // Replace x with mobile number
      delay(1000);
      //randNumber = random(999,9999);
      Serial.println("Emergency !!");
      mySerial1.println("Emergency !! Wild Animal detected !!");// The SMS text you want to send
      //mySerial1.println(randNumber);
      delay(100);
      mySerial1.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);

    }

    else if (incomingByte == "off") {

      digitalWrite(13, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
      Serial.write("Led off");

    }

    else{

     Serial.write("invald input");

    }

  }
  if (mySerial1.available()>0)
   Serial.write(mySerial1.read());

}

s