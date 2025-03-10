// Variables will change:
  int buttonState;	//will store the state of the button, pressed or not

// constants won't change:
  int inputButton = A0;	//The number of the pin to read the input from the button
  int toCam = 12;		//pin to send the signal to the cameras
  int OptoLed = 13;		//pin to power the led in front of the optogait
  int OnOffNum=4;		//number of sequence of blinking/off
  int numBlink=9000;		//number of time the led will blink
  int pause=200;  //pause delay in milliseconds
  int blinkFrequency=30000;  //the frequency of blinking in Hertz
  int delay_blink=(1000000/blinkFrequency)/2; //convert the frequency in microseconds

void setup() {
  // set the digital pin as output:  
  pinMode(inputButton,INPUT);	//Set the pin as input
  pinMode(toCam,OUTPUT);		//Set the pin as output
  pinMode(OptoLed,OUTPUT);		//Set the pin as output
}

void loop() {
  // here is where you'd put code that needs to be running all the time.
  buttonState=analogRead(inputButton);  //read the input pin
  if (buttonState<400){ //a digital read could have been used but 
    //the input tension doesn't clearly goes from 0 to 5V, hence an analog read allow more freedom
    delay(500); //wait half a second before executing the synchronisation sequence, 
    //to make sure both acquisition have started
  	for (int i = 0; i < OnOffNum; i++) {      
      for (int j = 0; j < numBlink; j++) {        
        PORTB = B00110000;  //The high/low state are driven directly by their port. 
        //It is faster than the write function and permits to switch the state of multiple outputs at the same time.
        delayMicroseconds(delay_blink);	// the time is in microseconds, 
        PORTB = B00010000;
  		  delayMicroseconds(delay_blink);	//
      }
      PORTB = B00000000;      
      delay(pause);
    }
  }
}
