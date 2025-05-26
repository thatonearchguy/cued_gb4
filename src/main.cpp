#include <Arduino.h>
#include <TimerOne.h>


// put function declarations here:
int myFunction(int, int);
void timer_actuate();
void wake_sprayer();

int modeSelect = 7;
int sprayButton = 9;

bool spray_op_state = false;


bool spray_state = true;

int ticks = 0;

int duty_cycle = 50;

int cycles_skipped;

void setup() {
  // put your setup code here, to run once:

  pinMode(modeSelect, INPUT);
  pinMode(sprayButton, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(1000);

  //wake_sprayer();


  Timer1.initialize(40000);
  Timer1.attachInterrupt(timer_actuate);
}

void wake_sprayer() {
  delay(100);
  digitalWrite(sprayButton, HIGH);
  delay(2000);
  digitalWrite(sprayButton, LOW);
  delay(2000);

  digitalWrite(sprayButton, HIGH);
  delay(2000);
  digitalWrite(sprayButton, LOW);
  delay(1000);
  digitalWrite(sprayButton, HIGH);
  delay(200);
  digitalWrite(sprayButton, LOW);
  delay(1000);
}

void timer_actuate() {

  if(duty_cycle == 0 && spray_state == false) return;

  if(duty_cycle == 100 && spray_state == true) return;


  if(spray_state == false)
  {

    if(duty_cycle < 50 && spray_op_state == false)
    {
      if (++cycles_skipped < 50 - duty_cycle) return;
    }

    if(spray_op_state == true)
    {
      spray_state = true;
    }

  }

  else if(spray_state == true)
  {
    if(duty_cycle > 50 && spray_op_state == false)
    {
      if(++cycles_skipped < duty_cycle - 50) return;
    }
    if(spray_op_state == true)
    {
      spray_state = false;
    }
  }

  cycles_skipped = 0;
  spray_op_state = !spray_op_state;
  digitalWrite(sprayButton, spray_op_state);


}



void loop() {


  // Behaves as transmitter
  if(digitalRead(modeSelect) == LOW) {
    int mq3Value = analogRead(A0);
    Serial.print("MQ3 concentration: ");
    Serial.println(mq3Value);


  }

  // Behaves as receiver
  else {
    Serial.println("Receiver Mode");
    //while (!Serial.available());
    //String x = Serial.readString();
    //Serial.print(x);
    //Serial.println(" ACK");

    //Power cycle the sprayer
    while(1)
    {
      for (int i = 30; i < 50; i +=2)
      {
        duty_cycle = i;
        delay(200);
        Serial.print("Duty cycle: ");
        Serial.println(duty_cycle);
      }
      for (int i = 50; i > 30; i -=2)
      {
        duty_cycle = i;
        delay(200);
        Serial.print("Duty cycle: ");
        Serial.println(duty_cycle);
      }
    }


  }
}
