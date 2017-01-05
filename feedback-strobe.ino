// output to n channel mosfet
#define MOTOR_PWM   16

// 0-3.3v analog input representing the desired motor speed
#define MOTOR_CTRL  14

// led count and their pins
#define NUM_LEDS 8
#define LED_B1  20 // inner blue
#define LED_B2  21
#define LED_B3  22
#define LED_B4  23 // outer blue
#define LED_W1  19 // outer white
#define LED_W2  18
#define LED_W3  17
#define LED_W4  13 // inner white

uint8_t leds[NUM_LEDS] = {LED_B1,LED_B2,LED_B3,LED_B4,LED_W1,LED_W2,LED_W3,LED_W4};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  uint8_t i;
  for( i=0; i<NUM_LEDS; i++ ){
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH); // off
  }

  pinMode(MOTOR_PWM, OUTPUT);
  analogWrite(MOTOR_PWM, 255);

}

void loop() {
  // put your main code here, to run repeatedly:
  int i;

  
  
  for( i=0; i<NUM_LEDS; i++ ){
    digitalWrite(leds[i], HIGH);
  }

  //delay(100);
  delay(analogRead(MOTOR_CTRL)>>2);

  for( i=NUM_LEDS-1; i>=0; i-- ){
    digitalWrite(leds[i], LOW);
  }

  delay(10);

  Serial.print("motor_ctrl: ");
  Serial.println( (analogRead(MOTOR_CTRL)>>2) );
}
