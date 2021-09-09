/*                                                                         BRAHMAPUTRA 1.0 FIRMWARE
 */

//----------------------------pin number definition----------------------------
const int rotate_pin=A1;       //rotate
const int throttle_pin=A2;     //throttle
const int weapon_pin=A3;        //weapon

//----------------------------pulse variable-----------------------------------
int rotate_pulse;
int throttle_pulse;
int weapon_pulse;

//----------------------------pwm variable-------------------------------------
int rotate_pwm;
int throttle_pwm;
int weapon_pwm;
//----------------------------general declarations-----------------------------
int deadzone=20;
//----------------------------output pins--------------------------------------
const int throttle_out=14;
const int throttle_dir=11;

const int rotate_out=13;
const int rotate_dir=10;

const int weapon_out=12;
const int weapon_dir=9;

 

void setup() {

pinMode(rotate_pin,INPUT);
pinMode(throttle_pin,INPUT);
pinMode(weapon_pin,INPUT);

Serial.begin(9600);
}



int pulsetopwm(int pulse)
{
  int pwm;
 if(pulse>1000)
  {
    pwm=map(pulse,1000,2000,-500,500);
    pwm=constrain(pwm,-255,255);
    return pwm;
  }
  else
  {
    pwm=0;
  }
 
  
  if(abs(pulse)<=deadzone)
  {
    pwm=0;
  }  
}

void drive(int throttle_pwm,int rotate_pwm)
{
    constrain(throttle_pwm,-255,255);
    constrain(rotate_pwm,-255,255);

   analogWrite(throttle_out,throttle_pwm);
}

void loop() {

  weapon_pulse=pulseIn(weapon_pin,HIGH,25000);
  throttle_pulse=pulseIn(throttle_pin,HIGH,25000);
  rotate_pulse=pulseIn(rotate_pin,HIGH,25000);

  weapon_pwm = pulsetopwm(weapon_pulse); 
  throttle_pwm = pulsetopwm(throttle_pulse);
  rotate_pwm = pulsetopwm(rotate_pulse);

   Serial.print(weapon_pwm);Serial.print("\t");Serial.print(throttle_pwm);Serial.print("\t");Serial.println(rotate_pwm);

  //throttle
  if(throttle_pwm>=0)
  {
  
  }




 
}
