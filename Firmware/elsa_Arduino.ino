int rc_1_radio_min = 1055;    //sets up the minimum value from receiver
int rc_2_radio_min = 1056;
int rc_3_radio_min = 1077;
int rc_4_radio_min = 1028;
int rc_1_radio_max = 1890;    //setup maximum value from receiver
int rc_2_radio_max = 1892;
int rc_3_radio_max = 1906;
int rc_4_radio_max = 1858;

// 3 is not trimmed
int rc_1_radio_trim = 1470;    //setup neutral value
int rc_2_radio_trim = 1476;
int rc_3_radio_trim = 1472;
int rc_4_radio_trim = 1446;


// assigns pin numbers for rc
int RC1= 13; // Manual throttle
int RC2= 14; //Choose mode
int RC3= 15; // Manual rotation
int RC4= 16;
int A_LED = 2;

int Motor1 = 1;   // voltage sent to motor, needs to be PWM pin 
int Motor2 = 3;   //  voltage sent to motor, needs to be PWM pin 
int Motor3 = 4;
int Motor4 = 5;

int twist_y = 0; //autonomous throttle
int twist_z = 0; //autonomous rotation

int front_right_motor_cal = 1; // needs to be modified later after testing
int front_left_motor_cal = 1;
int back_right_motor_cal = 1;
int back_left_motor_cal = 1;

int LEDcount = 0; //counting how many loops went through in autonomous mode











void setup() {
  // put your setup code here, to run once:


pinMode(RC1, INPUT); //receive input from pin 13
pinMode(RC2, INPUT);
pinMode(RC3, INPUT);
pinMode(RC4, INPUT);
pinMode(A_LED, OUTPUT); //send output to A_LED
pinMode(Motor1, OUTPUT);
pinMode(Motor2,OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:

}










void move_pwm(){

    uint16_t wheels[4];                         //an array of 16 bits unsigned integers
  
    int rc1_value = map(digitalRead(RC1), rc_1_radio_min, rc_1_radio_max, -500, 500); 
// rc1_value is assigned the value read from pin RC1 (Manual throttle)
int rc2_value = map(digitalRead(RC2), rc_2_radio_min, rc_2_radio_max, -500, 500); 
// rc2_value is assigned the value read from pin RC2 (Choose mode)
int rc3_value =map(digitalRead(RC3), rc_3_radio_min, rc_3_radio_max, -500, 500); 
// rc3_value is assigned the value read from pin RC3 (Manual rotation)

if (rc2_value <50 || rc2_value>50){
rc2_value=0
}
if (rc3_value <50 || rc3_value>50){
rc2_value=0

}if (rc1_value <50 || rc1_value>50){
rc2_value=0
}

//wireless estop if value from pin RC2 read is below 300
if(rc2_value < 300){ 
digitalWrite(A_LED,LOW);      
wheels[0]=1500; //front right wheel
wheels[1]=1500; //front left wheel
wheels[2]=1500; // rear right wheel
wheels[3]=1500; // rear left wheel
}
// manual control if value read from pin RC2 is above 300 or below 650
else if (rc2_value < 650){

 //each wheel is sent the result of the value for: “at rest” + (the rotation value - the throttle value) all multiplied by the respective motor calibration value.

wheels[0] = 1500+(rc3_value - rc1_value)*front_right_motor_cal; 
wheels[2] = 1500+(rc3_value - rc1_value)*back_right_motor_cal; 
wheels[1] = 1500+(rc3_value + rc1_value)*front_left_motor_cal + 30; 
//same computation as right motor, but different calibration value 
wheels[3] = 1500+(rc3_value + rc1_value)*back_left_motor_cal; //may need to add further calibration such as the +30 for wheel[1]
digitalWrite(A_LED, HIGH);

}

// autonomous mode if value read from pin RC2 is above 650
else {
//each wheel is sent the result of the value for : “at rest” + ( the autonomous rotation value - the autonomous throttle value) all multiplies by the respective motor calibration value.

wheels[0] = 1500 + (twist_z - twist_y) * front_right_motor_cal; 
wheels[2] = 1500 + (twist_z - twist_y) * back_right_motor_cal;
wheels[1] = 1500 + (twist_z + twist_y) * front_left_motor_cal; //may need to add further calibration such as the +30 for wheel[1] in manual
wheels[3] = 1500 + (twist_z + twist_y) * back_left_motor_cal;
  if (LEDcount < 20){
    digitalWrite(A_LED, HIGH);
  }
  else{
    digitalWrite(A_LED, LOW);
    if(LEDcount>40){
      LEDcount=0;
    }
  }
  LEDcount++;
}
analogWrite(Motor1, wheels[0]); // front-right wheel
analogWrite(Motor3, wheels[2]); // back-right 
analogWrite(Motor2, wheels[1]); // front-left 
analogWrite(Motor4, wheels[3]); // back-left
}











void setup_radio(void)
{    
 
 int rc_1radio_min = 1055;    //sets up the minimum value from receiver
 int rc_2radio_min = 1056;
 int rc_3radio_min = 1077;
 int rc_4radio_min = 1028;
 int  rc_1radio_max = 1890;    //setup maximum value from receiver
 int rc_2radio_max = 1892;
 int rc_3radio_max = 1906;
 int rc_4radio_max = 1858;



 // 3 is not trimmed
 rc_1.radio_trim = 1470;    //setup neutral value
 rc_2.radio_trim = 1476;
 rc_3.radio_trim = 1472;
 rc_4.radio_trim = 1446;

 rc_1= map(digitalRead(RC1), rc_1_radio_min, rc_1_radio_max, -500, 500);

sensorValue = map( sensorValue, sensorMin, sensorMax, -500, 500);
}
  






















































