#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

int modeSelect = 7;
int sprayButton = 2;

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  pinMode(modeSelect, INPUT);
  pinMode(sprayButton, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(1000);
}

void actuate(int timeout) {
  digitalWrite(sprayButton, HIGH);
  delay(timeout);
  digitalWrite(sprayButton, LOW);
}


void loop() {


  // Behaves as receiver
  if(digitalRead(modeSelect) == LOW) {
    int mq3Value = analogRead(A0);
    Serial.print("MQ3 concentration: ");
    Serial.println(mq3Value);


  }

  // Behaves as transmitter
  else {
    Serial.println("Receiver Mode");
    //while (!Serial.available());
    //String x = Serial.readString();
    //Serial.print(x);
    //Serial.println(" ACK");

    //Power cycle the sprayer
    actuate(1000);


    actuate(1000);


    while (1) {
      actuate(40);
      delay(35);
      actuate(40);

    }


  }



}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
