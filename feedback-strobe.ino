// FEEDBACK STROBE V2 
// MATT RUFFNER 
// NOVEMBER 2017

#include <TimerOne.h>
#include <PID_v1.h>

//Define PID variables
double Setpoint, Input, Output;

// NUMBER OF LEDS
#define NLEDS 8

//Specify the links and initial tuning parameters
double Kp=.5, Ki=0, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

/*------------------------------*/
/* HARDWARE CONNECTIONS         */
/*------------------------------*/
// INDIVIDUAL LED CONNECTIONS
#define LED1  12
#define LED2  11
#define LED3  10
#define LED4  9
#define LED5  17
#define LED6  16
#define LED7  15
#define LED8  14

// TO EASE ITERATIONS
const uint8_t leds[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};

/* PWM SIGNAL TO MOSFET */
#define MOTOR_PIN 6

/* IR REFLECTANCE SENSOR ANALOG IN */
#define IR_PIN    23//A9
#define IR_SAMPLE_PERIOD 5000 // ISR PERIOD IN MICROSECONDS
#define IR_SAMPLE_COUNT 200
float irSamples[IR_SAMPLE_COUNT];
unsigned long irSampleIndex = 0;
volatile unsigned long lastIrMinTimestamp = 0;
volatile unsigned long lastRotationPeriod = 0;
float currentRotationFreq = 0;


// LED BLINK CONTROL VARIABLES
bool ledState = LOW;
unsigned long lastStrobeTime = 0; 
unsigned long strobeOffTime = 120; 
unsigned long strobeOnTime =  5;

double blinkFreq = 1.0 / ((strobeOnTime + strobeOffTime)/1000.0);

volatile bool started = 0;
volatile bool newFreq = 0;

#define DEBUG 1

void setup()
{
  Serial.begin(9600);
  
  // SET LEDS AS OUTPUTS AND TURN THEM OFF
  if( DEBUG ) Serial.println("Setting LEDs as outputs...");
  for (uint8_t i=0; i<NLEDS; i++ ){
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }


  // SET MOTOR AS OUTPUT, TURN OFF
  if( DEBUG ) Serial.println("Initializing motor as output...");
  pinMode(MOTOR_PIN, OUTPUT);
  //driveMotor(255);


  // SET REFLECTANCE SENSOR AS INPUT
  if( DEBUG ) Serial.println("Setting up analog input sampling...");
  pinMode(IR_PIN, INPUT);
  Timer1.initialize(IR_SAMPLE_PERIOD);
  Timer1.attachInterrupt(sampleIRSensor);

  Serial.println("Setting PID variables");
  Input = currentRotationFreq;
  Setpoint = map(blinkFreq*10, 0, 150, 0, 2550)/10.0;
  myPID.SetOutputLimits(150,255);
  myPID.SetMode(AUTOMATIC);

  Serial.println("Starting...");

  driveMotor(200);
}

unsigned long lastFreqUpdate = 0;

void loop() 
{
  // put your main code here, to run repeatedly:

  if( millis() - 1000 > lastFreqUpdate ){

    noInterrupts();
    double t = currentRotationFreq;
    interrupts();
    
    Serial.print("current rot freq: ");
    Serial.println(t);
    lastFreqUpdate = millis();

    Input = map(t*10, 0, 150, 0, 2550)/10.0;

    myPID.Compute();
    
    Serial.print("new PID output: ");
    Serial.println(Output);

    driveMotor(Output);
  }

  
//  // UPDATE ROTATION SPEED
//  if( started && newFreq ){ 
//    noInterrupts();
//    Serial.print("rot freq: ");
//    Serial.println(currentRotationFreq);
//
//    
//    newFreq = 0;
//  }


  // drive LEDs
  if( millis() - lastStrobeTime > ( ledState ? strobeOnTime : strobeOffTime ) ){
    // update timestamp
    lastStrobeTime = millis();
    
    toggleStrobe();
  }

}

void sampleIRSensor()
{
  static bool state = 0;
  uint16_t n = (irSampleIndex++) % 200;
  irSamples[n] = (map(analogRead(IR_PIN), 0, 1023, 0, 10000)-5000)/10000.0;

  // with ir in from -0.5-0.5, dIr_dt can range from -50 to 50 
  if( irSampleIndex > 0 ){
    // derivative 2 most recent IR readings
    float dirdt = (irSamples[n]-irSamples[n-1]) / (IR_SAMPLE_PERIOD * 0.000001);
    unsigned long rn = millis();

    // trigger once a negative slope above a threshold is reached
    // when a positive dirdt is found it will be at the valley of the signal dip
    switch( state ){
    case 0:
      if( dirdt < -5 ){
        state = 1;
      }
      break;
    case 1:
      if( dirdt > 0 ){
        lastRotationPeriod = rn - lastIrMinTimestamp;
        lastIrMinTimestamp = rn;
        state = 0;
        currentRotationFreq = (float)(1000.0/lastRotationPeriod);
        //Serial.println(currentRotationFreq);
        if( !started ) started = 1;
        //newFreq = 1;
      }
    } 
  }
}

void toggleStrobe()
{
  uint8_t i;
  
  ledState = !ledState;

  for( i=0; i<NLEDS; i++ ){
    digitalWrite( leds[i], ledState );
  }
}

void driveMotor(uint8_t spd)
{
  uint8_t realSpeed = map(spd, 0, 255, 255, 0);
  analogWrite(MOTOR_PIN, realSpeed);
}

