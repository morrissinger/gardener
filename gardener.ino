#define pHSensorRX 10
#define pHSensorTX 11
#define eCSensorRX 9
#define eCSensorTX 8
#define usSensorEcho 6
#define usSensorTrigger 7
#define height 32

#include <SoftwareSerial.h>

SoftwareSerial pHSensor(pHSensorRX, pHSensorTX);
SoftwareSerial eCSensor(eCSensorRX, eCSensorTX);

char computerdata[20];
byte received_from_sensor=0;
byte received_from_computer=0;

char ph_data[20];
char ec_data[48];

float tempPH = 7.00;
float tempEC = 0.00;
float pH = 7.00;
int ec = 1000;
double waterLevel = 25.0;
int cmd = -1;

long duration, distance;
int offset;

void setup() {
  Serial.begin(9600);
  pHSensor.begin(9600);
  eCSensor.begin(9600);
  pinMode(usSensorTrigger, OUTPUT);
  pinMode(usSensorEcho, INPUT);
  
  pHSensor.listen();  
  pHSensor.print("C,0\r");
  delay(100);
  pHSensor.print("C,0\r");
  delay(100);
  
  eCSensor.listen();  
  eCSensor.print("SERIAL,9600\r");
  eCSensor.print("SERIAL,9600\r");
  eCSensor.print("C,0\r");
  delay(100);
  eCSensor.print("C,0\r");
  delay(100);
}

void readWaterLevel() {
  digitalWrite(usSensorTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(usSensorTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(usSensorTrigger, LOW);
  
  duration = pulseIn(usSensorEcho, HIGH);
  distance = (duration/2) / 29.1;

  offset = map(analogRead(A0), 0, 1023, -10, 10);
  
  if (distance >= 200 || distance < 0){
    waterLevel = -1;
  } else {
    waterLevel = (height - distance - offset);
  }
  delay(500);
}

void serialEventRun(void) {
  if (Serial.available()) serialEvent();
}

void serialEvent() {
  received_from_computer = Serial.readBytesUntil(13,computerdata,20);
  computerdata[received_from_computer]=0;
  
  
  if ((computerdata[0] == 'P') && (computerdata[1] == 'H')) {
    pHSensor.listen();  

    if ((computerdata[2] == 'C') && (computerdata[3] == 'A') && (computerdata[4] == 'L') && (computerdata[5] == 'I')) {
      if (computerdata[6] == 'L') {
        pHSensor.print("Cal,low,4.00\r");
      } else if (computerdata[6] == 'M') {
        pHSensor.print("Cal,mid,7.00\r");
      } else if (computerdata[6] == 'H') {
        pHSensor.print("Cal,high,10.00\r");
      } else if (computerdata[6] == '?') {
        pHSensor.print("Cal,?\r");
      }
    }  else if ((computerdata[2] == 'L') && (computerdata[3] == 'E') && (computerdata[4] == 'D') && (computerdata[5] == 'S')) {
      if (computerdata[6] == '0') {
        pHSensor.print("L,0\r");
      } else if (computerdata[6] == '1') {
        pHSensor.print("L,1\r");
      }
    } else if ((computerdata[2] == 'R') && (computerdata[3] == 'E') && (computerdata[4] == 'A') && (computerdata[5] == 'D')) {
      pHSensor.print("R,0\r");
    } else if ((computerdata[2] == 'M') && (computerdata[3] == 'O') && (computerdata[4] == 'D') && (computerdata[5] == 'E')) {
      if (computerdata[6] == '0') {
        pHSensor.print("C,0\r");
      } else if (computerdata[6] == '1') {
        pHSensor.print("C,1\r");
      }
    }
    
  } else if ((computerdata[0] == 'E') && (computerdata[1] == 'C')) {
    eCSensor.listen();  

    if ((computerdata[2] == 'K') && (computerdata[3] == 'A') && (computerdata[4] == 'L') && (computerdata[5] == 'I')) {
    } else if ((computerdata[2] == 'R') && (computerdata[3] == 'E') && (computerdata[4] == 'A') && (computerdata[5] == 'D')) {
      eCSensor.print("R,0\r");
    } else if ((computerdata[2] == 'M') && (computerdata[3] == 'O') && (computerdata[4] == 'D') && (computerdata[5] == 'E')) {
      if (computerdata[6] == '0') {
        eCSensor.print("C,0\r");
      } else if (computerdata[6] == '1') {
        eCSensor.print("C,1\r");
      }
    } else if ((computerdata[2] == 'L') && (computerdata[3] == 'E') && (computerdata[4] == 'D') && (computerdata[5] == 'S')) {
      if (computerdata[6] == '0') {
        eCSensor.print("L,0\r");
      } else if (computerdata[6] == '1') {
        eCSensor.print("L,1\r");
      }
    }  else if ((computerdata[2] == 'T') && (computerdata[3] == 'Y') && (computerdata[4] == 'P') && (computerdata[5] == 'E')) {
      if (computerdata[6] == '0') {
        eCSensor.print("K,0.1");
      } else if (computerdata[6] == '1') {
        eCSensor.print("K,1.0");
      } else if (computerdata[6] == '2') {
        eCSensor.print("K,10.0");
      }
    } else if ((computerdata[2] == 'C') && (computerdata[3] == 'A') && (computerdata[4] == 'L') && (computerdata[5] == 'I')) {
      if (computerdata[6] == 'D') {
        eCSensor.print("Cal,dry");
      } else if (computerdata[6] == 'L') {
        eCSensor.print("Cal,low,84");
      } else if (computerdata[6] == 'H') {
        eCSensor.print("Cal,high,1413");
      } else if (computerdata[6] == '?') {
        eCSensor.print("Cal,?");
      }
    }
  } else if ((computerdata[0] == 'W') && (computerdata[1] == 'L')) {
    readWaterLevel();
  } else {
    Serial.print(" Invalid request.");
  }
  Serial.print("\n");  
}  

void loop() {
    if(pHSensor.available() > 0) {
     received_from_sensor=pHSensor.readBytesUntil(13, ph_data, 20); //we read the data sent from pH Circuit until we see a <CR>. We also count how many character have been received.  
     ph_data[received_from_sensor] = 0;  //we add a 0 to the spot in the array just after the last character we received. This will stop us from transmitting incorrect data that may have been left in the buffer. 
     tempPH = atof(ph_data);
     if (tempPH > 0) {
       pH = tempPH;
       Serial.println(pH);
     }

  }
  
  if(eCSensor.available() > 0) {
    received_from_sensor=eCSensor.readBytesUntil(13,ec_data,48); //we read the data sent from EC Circuit until we see a <CR>. We also count how many character have been received.  
    ec_data[received_from_sensor]=0;
    tempEC = atof(strtok(ec_data, ","));
    if (tempEC > 0) {
      ec = (int)tempEC;
      Serial.println(ec);
    }
  }
  delay(1);
}
