#include<Servo.h>     //servo library for the ARM
#include<Stepper.h>   //stepper library for the Turning Tray

String input = "";
Servo arm;                     //instantiate arm servo
Stepper tray(200, 3, 4, 5, 6); //instantiate tray motor attaches to pins 8 9 10 11 and set at 200 steps per revulution

void setup() {               
  Serial.begin(9600);                    //Initialize serial communication, baud rate to 9600
  arm.attach(7);                         //attach servo to pin 7 enabling control
  arm.write(55);                         //default "up" postition for the arm
  tray.setSpeed(90);                     //set the speed of stepper motor to be 90PRM
  tray.step(0);                          //send pinout so torque on motor increases
}

void loop() {
  if (Serial.available()>0){            //waits for user input in the serial window. 
    input = Serial.readString();        //read the user input as a string 
    if(input == "U"){                   //compares the input with Valid Inputs
      Serial.print("U Move \n");        //prints out what move is made
      tilt();                           //series of tilts holds and twists to achieve that move
      tilt();
      hold();
      oCW();
      tilt();
      tilt();
      up();
    }
    else if(input == "U'"){
      Serial.print("U' Move \n");
      tilt();
      tilt();
      hold();
      oCCW();
      tilt();
      tilt();
      up();
    }
    else if(input == "U2"){
      Serial.print("U2 Move \n");
      tilt();
      tilt();
      hold();
      oDT();
      tilt();
      tilt();
      up();
    }
    else if(input == "F"){
      Serial.print("F Move \n");
      tilt();
      hold();
      oCW();
      up();
      DT();
      tilt();
      up();
      DT();
    }
    else if(input == "F'"){
      Serial.print("F' Move \n");
      tilt();
      hold();
      oCCW();
      up();
      DT();
      tilt();
      up();
      DT();
    }
    else if(input == "F2"){
      Serial.print("F2 Move \n");
      tilt();
      hold();
      oDT();
      up();
      DT();
      tilt();
      up();
      DT();
    }
    else if(input == "R"){
      Serial.print("R Move \n");
      up();
      CCW();
      tilt();
      oCW();
      up();
      DT();
      tilt();
      up();
      CCW();
    }
    else if(input == "R'"){
      Serial.print("R' Move \n");
      up();
      CCW();
      tilt();
      oCCW();
      up();
      DT();
      tilt();
      up();
      CCW();
    }
    else if(input == "R2"){
      Serial.print("R2 Move \n");
      up();
      CCW();
      tilt();
      oDT();
      up();
      DT();
      tilt();
      up();
      CCW();
    }
    else if(input == "B"){
      Serial.print("B Move \n");
      up();
      DT();
      tilt();
      hold();
      oCCW();
      up();
      DT();
      tilt();
      up();
    }
    else if(input == "B'"){
      Serial.print("B' Move \n");
      up();
      DT();
      tilt();
      hold();
      oCW();
      up();
      DT();
      tilt();
      up();
    }
    else if(input == "B2"){
      Serial.print("B2 Move \n");
      up();
      DT();
      tilt();
      hold();
      oDT();
      up();
      DT();
      tilt();
      up();
    }
    else if(input == "L"){
      Serial.print("L Move \n");
      up();
      CW();
      tilt();
      hold();
      oCW();
      up();
      DT();
      tilt();
      up();
      CW();
    }
    else if(input == "L'"){
      Serial.print("L' Move \n");
      up();
      CW();
      tilt();
      hold();
      oCCW();
      up();
      DT();
      tilt();
      up();
      CW();
    }
    else if(input == "L2"){
      Serial.print("L2 Move \n");
      up();
      CW();
      tilt();
      hold();
      oDT();
      up();
      DT();
      tilt();
      up();
      CW();
    }
    else if(input == "D"){
      Serial.print("D Move \n");
      hold();
      oCCW();
      up();
    }
    else if(input == "D'"){
      Serial.print("D' Move \n");
      hold();
      oCW();
      up();
      
    }
    else if(input == "D2"){
      Serial.print("D2 Move \n");
      hold();
      oDT();
      up();
    }
    else if(input == "x"){
      Serial.print("x rotation \n");
      tilt();
      up();
    }
    else if(input == "x'"){
      Serial.print("x' rotation \n");
      up();
      DT();
      tilt();
      up();
      DT();
    }
    else if(input == "x2"){
      Serial.print("x2 rotation \n");
      tilt();
      tilt();
      up();
    }
    else if(input == "y"){
      Serial.print("y rotation \n");
      up();
      CCW();
    }
    else if(input == "y'"){
      Serial.print("y' rotation \n");
      up();
      CW();
    }
    else if(input == "y2"){
      Serial.print("y2 rotation \n");
      up();
      DT();
    }
    else if(input == "z"){
      Serial.print("z rotation \n");
      up();
      CCW();
      tilt();
      up();
      CW();     
    }
    else if(input == "z'"){
      Serial.print("z' rotation \n");
      up();
      CW();
      tilt();
      up();
      CCW();     
    }
    else if(input == "z2"){
      Serial.print("z2 rotation \n");
      up();
      CCW();
      tilt();
      tilt();
      up();
      CW();   
    }
    else{
      Serial.print("Invalid \n");       //if the input is not valid prints out invalid and waits for input again
    }
  } 
}

/*=================================================================
MOTOR MOVEMENT CODE
tilt       -  tilts the cube 
hold       -  makes the arm hold the cube
up         -  raises the arm
(o)CW      - (overdrive) clockwise quarter turn
(o)CCW     - (overdrive) counter clockwise quarter turn
(o)DT      - (overdrive) half turn direction doesn't matter
Overdrive  - While turning, the cube resists the force of the motor. 
              This causes the tray to not complete it's motion, 
              while in code it has. To make up for this, overdrive
              is introduced to add 1 or 2 more steps ensuring that
              intended motion is completed
===================================================================*/

void tilt(){
  arm.write(85);
  delay(700);
  arm.write(175);
  delay(700);
  arm.write(80);
  delay(400);
  arm.write(90);
  delay(400);
}

void hold(){
  arm.write(90);
  delay(1000);
}

void up(){
  arm.write(55);
  delay(1000);
}

void CCW(){
  tray.step(-50);
  delay(500);
}

void CW(){
  tray.step(50);
  delay(500);
}

void DT(){
  tray.step(10);
  delay(500);
}

void oCCW(){
  tray.step(-51);
  delay(500);
}

void oCW(){
  tray.step(51);
  delay(500);
}

void oDT(){
  tray.step(102);
  delay(500);
}
