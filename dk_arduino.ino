#include<Wire.h>
//#include<TimerOne.h>
#define PWM2 10
#define DIR12 5
#define DIR22 4
#define PWM1 9
#define DIR11 7
#define DIR21 8

#define Kp 0.0045
#define Kd 0.00035
#define Ki 0.005

boolean x = 0, y = 0;
int a = 0,dem = 1,b=1;
int lw=0, rw=0, alpha1=0, cmd;
String a1;
double banhtrai=0, banhphai=0,vl=0,vr=0;
float xung1=0, xung2=0;
float T = 0.2, alpha=0.611, B = 17.5, v, t = 0;
//float t1=20,t2=45,t3=60,t4=85,t5=100,t6=125,t7=140,t8=155; 
float t1,t2,t3,t4,t5,t6,t7,t8;
double Etr1=0,Etr2=0; //Etr3,Etr4; 
double Ei1=0,Ei2=0; //Ei3,Ei4;
void Demxung1() //trai
{
  xung1++;
}
void Demxung2() //phai
{
  xung2++;
}
float Tocdo1() {
  float tocdo=((xung1/334)*(1/T)*60);
  xung1=0;
  return tocdo;
}
float Tocdo2() {
  float tocdo=((xung2/334)*(1/T)*60);
  xung2=0;
  return tocdo;
}
void Tocdo(){
  banhtrai = Tocdo1();
  banhphai = Tocdo2();
  lw += PID(vl,banhtrai,Ei1,Etr1);
  rw += PID(vr,banhphai,Ei2,Etr2);
  Serial.print("banhtrai = ");
  Serial.print(banhtrai);
  Serial.print(",");
  Serial.print("banhphai = ");
  Serial.println(banhphai);
//  Serial.print("rw = ");
//  Serial.println(rw);
//  Serial.print("lw = ");
//  Serial.println(lw);
//  Serial.print("t1 = ");
//  Serial.println(t1);
//  Serial.print("t2 = ");
//  Serial.println(t2);
//  Serial.print("t3= ");
//  Serial.println(t3);
//  Serial.print("t4 = ");
//  Serial.println(t4);
//  Serial.print("t5 = ");
//  Serial.println(t5);
//  Serial.print("t6 = ");
//  Serial.println(t6);
//  Serial.print("t7 = ");
//  Serial.println(t7);
//  Serial.print("t8 = ");
//  Serial.println(t8);
}
void setup(){
  pinMode(PWM1,OUTPUT); 
  pinMode(DIR11,OUTPUT);
  pinMode(DIR21,OUTPUT);
  pinMode(PWM2,OUTPUT); 
  pinMode(DIR12,OUTPUT);
  pinMode(DIR22,OUTPUT);
  attachInterrupt(1,Demxung2,FALLING);
  attachInterrupt(0,Demxung1,FALLING);
  Wire.begin(0x02);
  Wire.onReceive(receiveEvent);
//  Timer1.initialize(150000);  //don vi us
//  Timer1.attachInterrupt(Tocdo);
  cli();
  TCCR2A = 0x00;
  TCCR2B = 0x00;
  TIMSK2 = 0x00;
  
  TCCR2B = 0x07;
  TCNT2 = 0x0F;
  TIMSK2 = (1<<TOIE2);
  sei();
  Serial.begin(9600);
}
void loop() {
  if(Serial.available()){
    a1 = Serial.readString();
    a = a1.toInt();
  }
  if (a == 0){
    //Wire.begin(0x02);
    x = 1;
    y = 1;
    vl = 1500;
    vr = 1500;
    v = 10.472;
    t1 = 12.78*alpha;
    t2 = t1 + 41.54/cos(alpha);
    t3 = t2 + 12.78*alpha;
    t4 = t3 + 53;
    t5 = t4 + 12.78*alpha;
    t6 = t5 + 41.54/cos(alpha);
    t7 = t6 + 12.78*alpha;
    t8 = t7 + 3;
    analogWrite(PWM1, rw);
    analogWrite(PWM2, lw);
    delay(5);
  }
  if (a == 1){
//        Serial.print("t1 = ");
//        Serial.println(t1);
//        Serial.print("t2 = ");
//        Serial.println(t2);
//        Serial.print("t3 = ");
//        Serial.println(t3);
//        Serial.print("t4 = ");
//        Serial.println(t4);
//        Serial.print("t5 = ");
//        Serial.println(t5);
//        Serial.print("t6 = ");
//        Serial.println(t6);
//        Serial.print("t7 = ");
//        Serial.println(t7);
//        Serial.print("t8 = ");
//        Serial.println(t8);
     Wire.end();
     if(b==1){
        t = millis()/100;
        b=0;
     }
//     if (((millis()/100 - t) >= 0)&&((millis()/100 - t) < 5)){
//        x = 1;
//        y = 1;
//        vl = 1500;
//        vr = 1500;
//        lw = constrain(lw,50,255);
//        rw = constrain(rw,50,255);
//        analogWrite(PWM1, rw);
//        analogWrite(PWM2, lw);
////        Serial.println(1);
////        delay(5);
//     }
     if (((millis()/100 - t) >= 0)&&((millis()/100 - t) <= t1)){
        x = 1;
        y = 0;
        vl = 2222;
        vr = 2222;
        lw = constrain(lw,50,255);
        rw = constrain(rw,50,255);
        analogWrite(PWM1, rw);
        analogWrite(PWM2, lw);
//        Serial.println(1);
//        delay(5);
     }
     if (((millis()/100 - t) > t1)&&((millis()/100 - t) <= t2)){
        x = 1;
        y = 1;
        vl = 1500;
        vr = 1500;
        lw = constrain(lw,50,255);
        rw = constrain(rw,50,255);
        analogWrite(PWM1, rw);
        analogWrite(PWM2, lw);
//        Serial.println(1);
//        delay(5);
     }
     if (((millis()/100 - t) > t2)&&((millis()/100 - t) <= t3)){
        x = 0;
        y = 1;
        vl = 2222;
        vr = 2222;
        lw = constrain(lw,50,255);
        rw = constrain(rw,50,255);
        analogWrite(PWM1, rw);
        analogWrite(PWM2, lw);
//        Serial.println(1);
//        delay(5);
     }
     if ((millis()/100 - t > t3)&&(millis()/100 - t <= t4)){
        x = 1;
        y = 1;
        vl = 1500;
        vr = 1500;
        lw = constrain(lw,50,255);
        rw = constrain(rw,50,255);
        analogWrite(PWM1, rw);
        analogWrite(PWM2, lw);
//        Serial.println(1);
//        delay(5);
     }
     if (((millis()/100 - t) > t4)&&((millis()/100 - t) <= t5)){
        x = 0;
        y = 1;
        vl = 2222;
        vr = 2222;
        lw = constrain(lw,50,255);
        rw = constrain(rw,50,255);
        analogWrite(PWM1, rw);
        analogWrite(PWM2, lw);
//        Serial.println(1);
//        delay(5);
     }
     if (((millis()/100 - t) > t5)&&((millis()/100 - t) <= t6)){
        x = 1;
        y = 1;  
        vl = 1500;
        vr = 1500;
        lw = constrain(lw,50,255);
        rw = constrain(rw,50,255);
        analogWrite(PWM1, rw);
        analogWrite(PWM2, lw);
//        Serial.println(1);
//        delay(5);
     }
     if (((millis()/100 - t) > t6)&&((millis()/100 - t) <= t7)){
        x = 1;
        y = 0;
        vl = 2222;
        vr = 2222;
        lw = constrain(lw,50,255);
        rw = constrain(rw,50,255);
        analogWrite(PWM1, rw);
        analogWrite(PWM2, lw);
//        Serial.println(1);
//        delay(5);
     }
     if (((millis()/100 - t) > t7)&&((millis()/100 - t) <= t8)){
        x = 1;
        y = 1;
        vl = 1500;
        vr = 1500;
        lw = constrain(lw,50,255);
        rw = constrain(rw,50,255);
        analogWrite(PWM1, rw);
        analogWrite(PWM2, lw);
//        Serial.println(1);
//        delay(5);
     }
     if (((millis()/100 - t) > t8)&&((millis()/100 - t) <= t8+5)){
        b=1;
        Serial.println(t);
//        Serial.println(9);
        Wire.begin(0x02);   
        a=0;
      }
  }
  receiveEvent(4);
  dieukhien();
  if(a==2){
    analogWrite(PWM1, 0);
    analogWrite(PWM2, 0);
    digitalWrite(DIR11,LOW);
    digitalWrite(DIR21,LOW);
    digitalWrite(DIR12,LOW);
    digitalWrite(DIR22,LOW);
  }
}  
void receiveEvent(int h) {
  if(Wire.available()){
    cmd = Wire.read();
    delay(1);
    a = Wire.read();
    delay(1);
    alpha1 = Wire.read();
    delay(1);
    alpha = alpha1*3.141/180;
    //cmd = Wire.read();
    //delay(1);
    Serial.print("a = ");
    Serial.println(a);
    Serial.print("alpha = ");
    Serial.println(alpha);
  }
}

void dieukhien(){
 if (x==1){    // Bánh sau bên phải
    digitalWrite(DIR11,LOW);
    digitalWrite(DIR21,HIGH);
  } else if (x==0) {
    digitalWrite(DIR11,HIGH);
    digitalWrite(DIR21,LOW);
  }
  if (y == 1 ){
    digitalWrite(DIR12,HIGH);
    digitalWrite(DIR22,LOW);
  }
  else if (y==0){
    digitalWrite(DIR12,LOW);
    digitalWrite(DIR22,HIGH);
  } 
//  Serial.println(a);
}
double PID(float tocdodat, float tocdo, double Ei, double Etr){
//  float za = 1500/(abs(tocdodat)-(3*pow(tocdodat,2)/65620)+1400);
//  if (za>2.5){
//    za = 4;
//  }
  double E = (tocdodat - tocdo);
//  float zb = (abs(E)+500)/500;
  Ei += E;
  float Output = (Kp*E + Ki*Ei + Kd*(E-Etr));
  Etr = E;
  Output = constrain(Output, -240 ,240);
  return Output;
}
ISR(TIMER2_OVF_vect) {
    TCNT2 = 0x0F;
    dem++;
    if (dem == 16) {
      Tocdo();
      dem = 1;
//      if(banhtrai<400){
//        al = al+2;
//      } else if(banhtrai<4000){
//        al=al;
//      } else { al = al -3; }
//      if(banhphai<400){
//        ar = ar+2;
//      } else if(banhphai<4000){
//        ar=ar;
//      } else { ar = ar - 3; }
//      ar = constrain(ar,-5,60);
//      al = constrain(al,-5,60);
    }   
}
