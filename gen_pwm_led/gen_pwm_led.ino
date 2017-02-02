#define RL RED_LED
#define BL BLUE_LED
#define GL GREEN_LED

void setup() {
  // put your setup code here, to run once:
pinMode(RL,OUTPUT);
pinMode(BL,OUTPUT);
pinMode(GL,OUTPUT);
}
int rl=0, bl=0, gl=0;
void loop() {
  // put your main code here, to run repeatedly: 
  analogWrite(RL,rl);
  analogWrite(BL,bl);
  analogWrite(GL,gl);
  rl=(rl+random(3))%255;
  bl=(bl+random(3))%255;
  gl=(gl+random(3))%255;
  
  delay(5);
  }

