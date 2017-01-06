// feedback strobe firmware v1.0
// Matt Ruffner 2017

// output to n channel mosfet
#define MOTOR_PWM_PIN   16
#define MOTOR_PWM_MIN   100
#define MOTOR_PWM_MAX   255

// 0-3.3v analog input representing the desired motor speed
#define MOTOR_CTRL_PIN  14

// blink rate control voltage
#define STROBE_CTRL_PIN 15

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

// in milliseconds
#define STROBE_ON_TIME      10
#define STROBE_RATES        10
#define STROBE_OFF_MAX      STROBE_ON_TIME*STROBE_RATES

// pin defs for LEDs
uint8_t ledPins[NUM_LEDS] = {LED_B1,LED_B2,LED_B3,LED_B4,LED_W1,LED_W2,LED_W3,LED_W4};
uint8_t ledState = HIGH; // off initially

// for routine to update motor and strobe control voltages
unsigned long lastInputUpdate = 0;
uint8_t inputUpdatePeriod = 10;

// strobe control vars
unsigned long lastStrobeTime = 0; // timestamp of last signal transition
unsigned int strobeOffTime = STROBE_OFF_MAX; // start with slowest blink
unsigned int strobeSetpoint = 0; // raw input voltage representation
uint8_t strobeRateSelection = 0; // granular choice ranging from 1 to STROBE_RATES

// specific to motor control
uint16_t motorSetpoint = 0; // 12 bit control voltage input representation
uint8_t motorSetpointAsPWM = 0; // 8 bit PWM motor control value out

void setup() {
  uint8_t i;
  
  Serial.begin( 9600 );
  
  for( i=0; i<NUM_LEDS; i++ ){
    pinMode( ledPins[i], OUTPUT );
    digitalWrite( ledPins[i], ledState ); 
  }

  // setup motor PWM pin as output, not spinning
  pinMode( MOTOR_PWM_PIN, OUTPUT );
  analogWrite( MOTOR_PWM_PIN, 0 );


  // dump blink frequencies for this setup
  Serial.println("Blink rates:");
  for( i=1; i<=STROBE_RATES; i++ ){
    float freq = 1.0/( (STROBE_ON_TIME/1000.0) + i*(STROBE_ON_TIME/1000.0) );
    Serial.println(freq);
  }
}


// main exectution loop
// at 48mhz, these .001 second granularity delays are no problem
void loop() {

  // compare time is based on stobe state allowing for a non 50% duty sycle
  if( millis() - lastStrobeTime > ( ledState ? strobeOffTime : STROBE_ON_TIME ) ){
    // update timestamp
    lastStrobeTime = millis();
    
    toggleStrobe();
  }


  if( millis() - lastInputUpdate > inputUpdatePeriod ){
    // update timestamp
    lastInputUpdate = millis();
    
    updateMotorControl();
    updateBlinkControl();
  }
  
}

void toggleStrobe() {
  uint8_t i;
  
  ledState = !ledState;

  for( i=0; i<NUM_LEDS; i++ ){
    digitalWrite( ledPins[i], ledState );
  }
}

void updateMotorControl() {
  // read target relative motor speed
  motorSetpoint = analogRead ( MOTOR_CTRL_PIN );

  // target speed to PWM out is not 1 to 1, need to scale  with 
  // our minimum PWM value in mind
  motorSetpointAsPWM = map( motorSetpoint, 0, 1023, MOTOR_PWM_MIN, MOTOR_PWM_MAX );

  // updated motor speed
  analogWrite( MOTOR_PWM_PIN, motorSetpointAsPWM );
}

void updateBlinkControl() {
  // update control value from either the DAQ or potentiometer
  strobeSetpoint = analogRead( STROBE_CTRL_PIN );

  // rescale this to a granular 'selection' of rates
  strobeRateSelection = map( strobeSetpoint, 0, 1023, 1, STROBE_RATES );

  // convert to a delayable amount of time in increments of the pulse width
  strobeOffTime = strobeRateSelection * STROBE_ON_TIME;
}

