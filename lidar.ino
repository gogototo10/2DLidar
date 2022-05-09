
#include <VL53L1X.h>
#include <Wire.h>
VL53L1X sensor;

#define DIVCOUNT 23

unsigned long int count = 0;
int motorStepPin = 11;
int motorDirPin = 5;
int photointerruptPin = A0;
int16_t ditance[150];
unsigned long int countI = 0;



void motorinit()
{

  pinMode(motorStepPin, OUTPUT);
  pinMode(motorDirPin, OUTPUT);
  digitalWrite(motorDirPin, LOW);
  digitalWrite(motorStepPin, LOW);
}
void photoInteInit()
{
  pinMode(photointerruptPin, INPUT);
}
void VL53l0XInit()
{
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    while (1);
  }


  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);


  sensor.startContinuous(50);
}

void loopphothInter()
{
  static bool prephotoState = true;
  if (analogRead(photointerruptPin) < 100 && prephotoState == true ) //하강
  {
    prephotoState = false;

  }
  else if (analogRead(photointerruptPin) > 300 && prephotoState == false) //상승
  {
    prephotoState = true;
    for (int i = 0; i < sizeof(ditance) / sizeof(ditance[0]); i++)
    {
      if (ditance[i] > 0)
      {
        Serial.print(ditance[i]);
        Serial.print(",");
      }
    }
    Serial.println();
    for (int i = 0; i < sizeof(ditance) / sizeof(ditance[0]); i++)
    {
      ditance[i] = 0;
    }
    count = 0;
    countI = 0;

  }
}
void loopMotor()
{

  static long int premillis = 0;
  if (millis() - premillis > 1)
  {
    count++;
    digitalWrite(motorStepPin, !digitalRead(motorStepPin));
    if (count % 50 == 0)
    {
      if (countI < (sizeof(ditance) / sizeof(ditance[0])) )
      {
        ditance[countI++] = readVL530X();
        //Serial.println(readVL530X());
      }
    }
    premillis = millis();
  }

}
int16_t readVL530X()
{
  int16_t distance;

  distance = sensor.read();
  if (sensor.timeoutOccurred())
  {
    //Serial.print(" TIMEOUT");
  }
  return distance;

}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  motorinit();
  photoInteInit();
  VL53l0XInit();
}

void loop()
{
  // put your main code here, to run repeatedly:
  loopphothInter();
  loopMotor();

}
