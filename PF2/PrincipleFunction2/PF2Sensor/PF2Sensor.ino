
/*
   proposed sensor configuration
   front of vehnical is pointing up 
 * = vehical 
 s = sensor 
 t = tape
 
        tt
        tt 
        ss 
        tt
       **** 
      ******
      ******
       **** 
        tt

*/

const int maxSpeed = 255;


const int opticalSensor0Pin = A5;
const int opticalSensor1Pin = A4;
//const int opticalSensor2Pin = A4;
//const int opticalSensor3Pin = A5;



const int leftMotorPower = 5; //E1 (left wheel speed)
const int leftMotorPolarity = 4; //M1 (left wheel) , LOW is forward
const int rightMotorPower = 6; //E1 (right wheel speed)
const int rightMotorPolarity = 7; //M1 (right wheel), HIGH is forward

const int leftFwd = HIGH;
const int leftBwd = LOW;

const int rightFwd = HIGH;
const int rightBwd = LOW;





int opticalSensors[] = {0,0,0,0};

int THRESHOLD = 200; // TODO update this value 

// optical[0] is furthest left sensor
// optical[3] is furthest right sensor


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  
  pinMode(opticalSensor0Pin, INPUT);
  pinMode(opticalSensor1Pin, INPUT);
//  pinMode(opticalSensor2Pin, INPUT);
//  pinMode(opticalSensor3Pin, INPUT);




}


void loop() {
  Serial.print(analogRead(opticalSensor0Pin));
  Serial.print("test");
 Serial.println(analogRead(opticalSensor1Pin));

//  principleFunction2();
}




void principleFunction2() {
  readSensors();
  updateDrive();
}



void updateDrive() {
  
  if (!opticalSensors[0] && !opticalSensors[1]) {
    fullSpeed();
    return; 
  } else if (!opticalSensors[0] && opticalSensors[1]) {
    // off to the right
    reduceLeft(1);
  } else if (opticalSensors[0] && !opticalSensors[1]) {
    reduceRight(1);
  } else if (opticalSensors[0] && opticalSensors[1]) {
    stopSpeed();
  }

 /*
  if (!opticalSensors[0] && opticalSensors[1] && opticalSensors[2] && !opticalSensors[3]) {
    stopSpeed();    
  }


  if (opticalSensors[2]) {
    // we're going off to the right
    if (!opticalSensors[0]) {
      reduceLeft(2);
    } else {
      reduceLeft(1);      
    }
  } else if (opticalSensors[1]) {
    // we're going off to the left
    if (!opticalSensors[3]) {
      reduceRight(2);
    } else {
      reduceRight(1);
    }
  }
*/
}

// reduce speed of left motor depending on value of spd
// if spd == 1 reduce a bit, if spd == 2 reduce a lot
void reduceLeft(int spd) {
  if (spd == 1) {
    analogWrite(leftMotorPower, maxSpeed - 20);
  } else if (spd == 2) {
    analogWrite(leftMotorPower, maxSpeed - 50);
  }  
} 

// reduce speed of right motor
// if spd == 1 reduce a bit, if spd == 2 reduce a lot
void reduceRight(int spd) {
  if (spd == 1) {
    analogWrite(rightMotorPower, maxSpeed - 20);
  } else if (spd == 2) {
    analogWrite(rightMotorPower, maxSpeed - 50);
  }  
}

// set max speed of motors 
void fullSpeed() {
  analogWrite(leftMotorPower, maxSpeed);
  analogWrite(rightMotorPower, maxSpeed);
}

// set max speed of motors 
void stopSpeed() {
  analogWrite(leftMotorPower, 0);
  analogWrite(rightMotorPower, 0);
}


// disable sensors for bit to wait for crossing
void crossing() {
  delay(200);
  return; 
}






// reads the 4 sensors and updates sensors array 
void readSensors() { 

  if (analogRead(opticalSensor0Pin) > THRESHOLD) {
    opticalSensors[0] = 1;
  } else {
    opticalSensors[0] = 0;
  }

  if (analogRead(opticalSensor1Pin) > THRESHOLD) {
    opticalSensors[1] = 1;
  } else {
    opticalSensors[1] = 0;
  }
/*
  if (analogRead(opticalSensor2Pin) > THRESHOLD) {
    opticalSensors[2] = 1;
  } else {
    opticalSensors[2] = 0;
  }

  if (analogRead(opticalSensor3Pin) > THRESHOLD) {
    opticalSensors[3] = 1;
  } else {
    opticalSensors[3] = 0;
  }
*/
  return; 
}
