// Interactive Moodlight
// Matt Nupen
// 2013 - sciencearium.com
//
// Credits:
// http://fightpc.blogspot.com/2008/03/arduino-mood-light.html
// http://splinter.com.au/blog/?p=29
// http://eduardofv.com/read_post/179-Arduino-RGB-LED-HSV-Color-Wheel-

// Led Pins
int redPin = 9;
int greenPin = 10;
int bluePin = 11;

int r=0;                           
int g=0;                           
int b=0;

// Buttons for changing Colors
int rButtonPin = 0;
int gButtonPin = 1;
int bButtonPin = 2;

long rLastDebounceTime = 0;
long gLastDebounceTime = 0;
long bLastDebounceTime = 0;

int rButtonState; 
int gButtonState; 
int bButtonState; 

int rLastButtonState = LOW;
int gLastButtonState = LOW;
int bLastButtonState = LOW;

// Analog Sensors
//int potPin1 = A0;
//int potPin2 = A1;
//int potPin3 = A2;
int rVal = 0;
int gVal = 0;
int bVal = 0;

// Photoresistor (light sensor)
int photoPin = A0;
int photoVal = 0;


int numberOfModes = 6; //how many modes are possible in the switch statement
int fadeSpeed = 100; //how quickly fade modes will change

volatile int buttonCounter = 0;
volatile int state = LOW;
volatile boolean noChange = true;

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

volatile long lastDebounceTime = 0;   // the last time the interrupt was triggered
volatile int reading;
#define debounceDelay 50    // the debounce time in ms; decrease if quick button presses are ignored, increase
                             //if you get noise (multipule button clicks detected by the code when you only pressed it once)
#define buttonPin 0 //digital pin 3, interrupt 0


void setup(){ 
  attachInterrupt(buttonPin, buttonEvent, RISING);
  Serial.begin(9600);
  
  pinMode(photoPin, INPUT);
  pinMode(rButtonPin, INPUT);
  pinMode(gButtonPin, INPUT);
  pinMode(bButtonPin, INPUT);
  pinMode(buttonPin, INPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
} 



void loop() {
  
  switch(buttonCounter){
  case 0:
    Serial.println("RANDOM FADING"); 
    slowRandomFading(255);
    break;
  case 1:
    Serial.println("RANDOM COLOR");
    randomColor(255); 
    break;
  case 2: 
    Serial.println("RAINBOW");
    rainbow(); 
    break;
  case 3: 
    Serial.println("CANDLE");
    candle(200); 
    break;
  case 4:
    Serial.println("USER CONTROLLED");
    custom();
    break;
  case 5:
    Serial.println("Full Spectrum");
    fullSpectrum();
    break;
  case 6:
    Serial.println("Off");
    lightsOff();
    break;
  default:
    Serial.println("Off"); 
    lightsOff(); 
    break;
  } 
  

  Serial.println(buttonCounter);
  
  delay(20);
  
}


