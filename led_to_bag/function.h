//function to reset the variables when the player loose
void lose();

//function to increase the number of object led to the bag and make the white led (pos 0) fading
void win();

//function to set the state of a led, if the "amount" is equal to 0 the led is switched off, otherwise it's set to on
void light(int led, int amount);

//function to set the intro of the game
void initialBlinking();

//main function of the game: it changes the state of the leds when the button TD is pressed, related to the value of "pushes" and "randLed" 
void bringToWhite(int randLed);
