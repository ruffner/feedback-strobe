#define IR_IN   14

#define MOTOR   10

#define NUM_LEDS 8

#define LED_B1  20
#define LED_B2  21
#define LED_B3  22
#define LED_B4  23
#define LED_W1  19
#define LED_W2  18
#define LED_W3  17
#define LED_W4  16

uint8_t leds[NUM_LEDS] = {LED_B1,LED_B2,LED_B3,LED_B4,LED_W1,LED_W2,LED_W3,LED_W4};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  uint8_t i;
  for( i=0; i<NUM_LEDS; i++ ){
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  pinMode(IR_IN, INPUT);

  pinMode(MOTOR, OUTPUT);
  analogWrite(MOTOR, 100);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
  
  for( i=0; i<NUM_LEDS; i++ ){
    digitalWrite(leds[i], HIGH);
    delay(50);
  }

  for( i=NUM_LEDS-1; i>=0; i-- ){
    digitalWrite(leds[i], LOW);
    delay(50);
  }


  Serial.println(analogRead(IR_IN));
}
