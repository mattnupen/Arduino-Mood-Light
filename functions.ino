void buttonEvent(){
  reading = digitalRead(buttonPin);
  // If the switch changed, due to noise or pressing:
  if(reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay){ //if current time minus the last trigger time is greater than
    //the delay (debounce) time, button is completley closed.
    lastDebounceTime = millis();
    buttonCounter++;
    noChange = false;

    //Serial.println(buttonCounter);
    //digitalWrite(13,HIGH);
  }
  if(buttonCounter > numberOfModes){
    buttonCounter = 0;
  }
  lastButtonState = reading;


}


//Sets the current color for the RGB LED
void setLedColor(int r, int g, int b) {
  //Note that we are reducing 1/4 the intensity for the green and blue components because 
  //  the red one is too dim on my LED. You may want to adjust that.
  analogWrite(redPin,r);
  analogWrite(greenPin,g/3);
  analogWrite(bluePin,b/3);
}


void randomColor(int max) {
  while(noChange) {
    setLedColor(random(max),random(max),random(max));
    delay(fadeSpeed);
  }
  noChange = true;
}


void slowRandomFading(int max) // slow random fading 
{ 
  int color,i,value;
  int time = fadeSpeed/10; 
  while(noChange) {
    color=random(1,4); 
    value=random(0,max);
    switch(color) {
    case 1: 
      if(r>value) for(i=r;i>value;i--) {
        setLedColor(i,g,b); 
        delay(time); 
      }
      else for(i=r;i<value;i++) {
        setLedColor(i,g,b); 
        delay(time); 
      }
      r=value;
      break;
    case 2: 
      if(g>value) for(i=g;i>value;i--) {
        setLedColor(r,i,b); 
        delay(time); 
      }
      else for(i=g;i<value;i++) {
        setLedColor(r,i,b); 
        delay(time); 
      }
      g=value;
      break;
    case 3: 
      if(b>value) for(i=b;i>value;i--) {
        setLedColor(r,g,i); 
        delay(time); 
      }
      else for(i=b;i<value;i++) {
        setLedColor(r,g,i); 
        delay(time); 
      }
      b=value;
      break;
    } 
  }
  noChange = true;
} 


void candle(int max) {
  int value;
  while(noChange) {
    value=random(max/4,max);
    setLedColor(value, value*5/10-random(max/10), 0);
    delay(30+random(40));
  } 
  noChange = true;
}

// not using
void rainbow2(int max) {
  while(noChange) {
    int timer = fadeSpeed;
    setLedColor(max,0,0); 
    delay(timer); // red
    setLedColor(0,max,0); 
    delay(timer); // green
    setLedColor(0,0,max); 
    delay(timer); // blue
    setLedColor(max,max,0); 
    delay(timer); // yellow
    setLedColor(max/2,0,max/2); 
    delay(timer); // purple
    setLedColor(max,0,max); 
    delay(timer); // fuschia
    setLedColor(0,0,max/2); 
    delay(timer); // navy
    setLedColor(0,max/2,max/2); 
    delay(timer); // teal
    setLedColor(0,max,max); 
    delay(timer); // aqua
    setLedColor(max/2,max/2,0); 
    delay(timer); // olive
    setLedColor(0,max/2,0); 
    delay(timer); // lime
    setLedColor(max/2,max/2,max/2); 
    delay(timer); // grey
    setLedColor(max,max,max); 
    delay(timer); // white    
  }
  noChange = true;
}

void rainbow() {
  while(noChange) {

    for(int i = 0; i < 256; i++) {
      setLedColor(255,i,0); 
      delay(1);  
    }
    for(int i = 0; i < 256; i++) {
      setLedColor(255-i,255,0); 
      delay(1);  
    }  
    for(int i = 0; i < 256; i++) {
      setLedColor(0,255,i); 
      delay(1);  
    }
    for(int i = 0; i < 256; i++) {
      setLedColor(0,255-i,255); 
      delay(1);  
    }
    for(int i = 0; i < 256; i++) {
      setLedColor(i,0,255); 
      delay(1);  
    }
    for(int i = 0; i < 256; i++) {
      setLedColor(255,0,255-i); 
      delay(1);  
    }
  } 
  noChange = true;
}

void custom(){
  r = 0;
  g = 0;
  b = 0;
  while(noChange) {
    if(digitalRead(rButtonPin) == HIGH){
      r+2;
      delay(10);
    }

    if(digitalRead(gButtonPin) == HIGH){
      g+2;
      delay(10);
    }

    if(digitalRead(bButtonPin) == HIGH){
      b+2;
      delay(10);
    }
    //set colors
    if(r >= 254){
      r = 0;
    }

    if(g >= 254){
      g = 0;
    }

    if(b >= 254){
      b = 0;
    }

    setLedColor(r,g,b);
    /*
    Serial.print("r = ");
    Serial.print(r);
    Serial.print("\t");
    Serial.print("g = ");
    Serial.print(g);
    Serial.print("\t");
    Serial.print("b = ");
    Serial.println(b);
    */
    delay(10);
  }

  noChange = true;
}

void nightLight(){
  while(noChange) {
    photoVal = analogRead(photoPin);
    if(photoVal < 100){
      setLedColor(255,255,255);
    }
  }
  noChange = true;
}


//http://eduardofv.com/read_post/179-Arduino-RGB-LED-HSV-Color-Wheel-
void fullSpectrum(){
  while(noChange) {
    //The Hue value will vary from 0 to 360, which represents degrees in the color wheel
    for(int hue=0;hue<360;hue++)
    {
      setLedColorHSV(hue,1,1); //We are using Saturation and Value constant at 1
      delay(fadeSpeed/10);
    }

  }
  noChange = true;
}

//Convert a given HSV (Hue Saturation Value) to setLedColor(Red Green Blue) and set the led to the color
//  h is hue value, integer between 0 and 360
//  s is saturation value, double between 0 and 1
//  v is value, double between 0 and 1
//http://splinter.com.au/blog/?p=29
void setLedColorHSV(int h, double s, double v) {
  //this is the algorithm to convert from RGB to HSV
  double r=0; 
  double g=0; 
  double b=0;

  double hf=h/60.0;

  int i=(int)floor(h/60.0);
  double f = h/60.0 - i;
  double pv = v * (1 - s);
  double qv = v * (1 - s*f);
  double tv = v * (1 - s * (1 - f));

  switch (i)
  {
  case 0: //rojo dominante
    r = v;
    g = tv;
    b = pv;
    break;
  case 1: //verde
    r = qv;
    g = v;
    b = pv;
    break;
  case 2: 
    r = pv;
    g = v;
    b = tv;
    break;
  case 3: //azul
    r = pv;
    g = qv;
    b = v;
    break;
  case 4:
    r = tv;
    g = pv;
    b = v;
    break;
  case 5: //rojo
    r = v;
    g = pv;
    b = qv;
    break;
  }

  //set each component to a integer value between 0 and 255
  int red=constrain((int)255*r,0,255);
  int green=constrain((int)255*g,0,255);
  int blue=constrain((int)255*b,0,255);

  setLedColor(red,green,blue);
}

void lightsOff(){
  while(noChange) {
    setLedColor(0,0,0);
  }
  noChange = true;
}


