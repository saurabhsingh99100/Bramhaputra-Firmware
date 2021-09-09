/*                                                         BRAHMAPUTRA FIRMWARE 1.0
 *                                                          
 */
//-------INPUT PINS-------------------
const int rotate_pin=A1;     //ch1
const int throttle_pin=A2;   //ch2
const int weapon_pin=A3;     //ch3

//-------DEADZONE--------------------
int deadzone=50;

//-------OUTPUT PINS-----------------
const int weapon_out=5;
const int weapon_dir=3;



const int lmotor_out=11;
const int lmotor_dir=12;

const int rmotor_out=10;
const int rmotor_dir=9;


void setup()
{
//----------PINMODE DEFINITIONS------------
pinMode(throttle_pin,INPUT);
pinMode(rotate_pin,INPUT);
pinMode(weapon_pin,INPUT);

pinMode(lmotor_dir,OUTPUT);
pinMode(rmotor_dir,OUTPUT);
pinMode(weapon_dir,OUTPUT);

//-----SERIAL COMMUNICATION INITIATION-----
//Serial.begin(115200); 
}

//---------CONVERT PULSE TO PWM----------
int pulsetopwm(int pulse)
{
  int pwm;
  if (pulse!=0)
  {
    
    pwm=map(pulse,1000,2000,-500,500);
    pwm=constrain(pwm,-255,255);
  }
  else
  { 
    pwm=0;
  }
  if (abs(pwm)<=deadzone)             //DEADZONE 
  {
    pwm=0;
  }
return pwm;
}



//----------------DRIVE-----------------
void drive(int lmotor,int rmotor)
{

lmotor=constrain(lmotor,-255,255);
rmotor=constrain(rmotor,-255,255);

//Serial.print(lmotor);Serial.print("\t");Serial.print(rmotor);

if(lmotor>=0){
  digitalWrite(lmotor_dir,LOW);
  }
else
{
  digitalWrite(lmotor_dir,HIGH); 
}
if(rmotor>=0){
  digitalWrite(rmotor_dir,LOW);
  }
else
{
  digitalWrite(rmotor_dir,HIGH); 
}


analogWrite(lmotor_out,abs(lmotor));
analogWrite(rmotor_out,abs(rmotor));

 
}

void loop()
{
  int throttle_pulse;
  int rotate_pulse;
  int weapon_pulse;

  //----------READ PULSE LENGTH-------------
  weapon_pulse=pulseIn(weapon_pin,HIGH,50000);
  throttle_pulse=pulseIn(throttle_pin,HIGH,50000);
  rotate_pulse=pulseIn(rotate_pin,HIGH,50000);

  delay(10);
  //--------CONVERT TO PWM VALUES-----------
  int weapon_pwm=pulsetopwm(weapon_pulse);
  int throttle_pwm=pulsetopwm(throttle_pulse);
  int rotate_pwm=pulsetopwm(rotate_pulse);

  
 
  
  
  int lmotor=throttle_pwm+rotate_pwm;            // calculate values
  int rmotor=throttle_pwm-rotate_pwm;

  drive(lmotor,rmotor);                      // send values to drive function
  
  
  if(weapon_pwm>=0)
  {
    digitalWrite(weapon_dir,LOW);    
  }
  else{
    digitalWrite(weapon_dir,HIGH);
  }

  weapon_pwm=map(weapon_pwm,-255,255,-127,127);
  analogWrite(weapon_out,abs(weapon_pwm));

  
 // Serial.print("\t");Serial.println(abs(weapon_pwm));


  
  
}
