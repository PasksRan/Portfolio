#define LED_RED 11
#define LED_GREEN 9
#define LED_BLUE 7
#define LED_YELLOW 5
#define LED_CORRECT 4
#define LED_WRONG 2

#define BUTTON_RED 12
#define BUTTON_GREEN 10
#define BUTTON_BLUE 8
#define BUTTON_YELLOW 6

#define BUZZER 3

#define RED_TONE 220
#define GREEN_TONE 262
#define BLUE_TONE 330
#define YELLOW_TONE 392
#define TONE_DURATION 250

int GAME_SPEED = 250;
int GAME_STATUS	= 0;
const int GAME_MAX_SEQUENCE	= 50;
int GAME_SEQUENCE[GAME_MAX_SEQUENCE];
int GAME_STEP	= 0;
int READ_STEP	= 0;

void setup(){
	Serial.begin(9600);
  	randomSeed(analogRead(0));
  	pinMode(LED_RED,OUTPUT);
  	pinMode(LED_GREEN,OUTPUT);
  	pinMode(LED_BLUE,OUTPUT);
  	pinMode(LED_YELLOW,OUTPUT);
  	pinMode(LED_CORRECT,OUTPUT);
  	pinMode(LED_WRONG,OUTPUT);
  	pinMode(BUTTON_RED,INPUT_PULLUP);
  	pinMode(BUTTON_GREEN,INPUT_PULLUP);
  	pinMode(BUTTON_BLUE,INPUT_PULLUP);
  	pinMode(BUTTON_YELLOW,INPUT_PULLUP);
  	pinMode(BUZZER,OUTPUT);
}
  
  
void loop(){
  switch(GAME_STATUS){
  	case 0:
    	resetGame();
    	break;
    case 1:
    	playSequence();
    	break;
    case 2:
    	readSequence();
    	break;
    case 3:
    	gameOver();
    	break;
  }
}

void resetGame(){
	READ_STEP = 0;
    GAME_STEP = 0;
  
  for(int i=0; i<GAME_MAX_SEQUENCE; i++){
  	GAME_SEQUENCE[i] = random(4)+ 1;
  }
  GAME_STATUS = 1;
} 

void playSequence(){
  for(int i = 0; i<=GAME_STEP; i++){
  	Serial.print("Set LED");
    Serial.println(GAME_SEQUENCE[i]);
    delay(GAME_SPEED*2);
    setLED(GAME_SEQUENCE[i]);
    playTone(GAME_SEQUENCE[i]);
    delay(GAME_SPEED);
    clearLEDs();
  }
  GAME_STATUS = 2;
}

void readSequence(){
	int button_value = readButtons();
  if (button_value >0){
    if(button_value == GAME_SEQUENCE[READ_STEP]){
    	setLED(button_value);
      	playTone(button_value);
      digitalWrite(LED_CORRECT,HIGH);
      delay(GAME_SPEED);
      clearLEDs();
      digitalWrite(LED_CORRECT, LOW);
      
      if (GAME_SPEED >100){
      	GAME_SPEED = GAME_SPEED - 15;
      }
      Serial.println("Correct!");
      
      if(READ_STEP == GAME_STEP){
      READ_STEP=0;
        GAME_STEP++;
        GAME_STATUS = 1;
        Serial.println("Next step");
        
        setLEDs(true,true,true,true);
        delay(GAME_SPEED);
        setLEDs(false,false,false,false);
      }
      else{
      	READ_STEP++;	
      }
      delay(10);
    }
    else{
    	GAME_STATUS = 3;
      Serial.println("Game over!");
    }
  }
  delay(10);
}
void gameOver(){
	digitalWrite(LED_WRONG, HIGH);
  
  	tone(BUZZER, 98, TONE_DURATION);
  	delay(TONE_DURATION);
  	tone(BUZZER, 87, TONE_DURATION);
  	delay(TONE_DURATION);
  	delay(GAME_SPEED);
}

void setLED(int color){
  clearLEDs();
  switch(color){
  	case 1:
    	digitalWrite(LED_RED, HIGH);
    	break;
    case 2:
    	digitalWrite(LED_GREEN, HIGH);
    	break;
    case 3:
    	digitalWrite(LED_BLUE, HIGH);
    	break;
    case 4:
    	digitalWrite(LED_YELLOW, HIGH);
    	break;
    default:
    	break;
  }
}

void playTone(int color){
  int toneFrequency = 0;
  switch (color){
  	case 1:
    	toneFrequency = RED_TONE;
    	break;
    case 2:
    	toneFrequency = GREEN_TONE;
    	break;
    case 3:
    	toneFrequency = BLUE_TONE;
    	break;
    case 4:
    	toneFrequency = YELLOW_TONE;
    	break;
    default:
    	return;
  }
  
  tone(BUZZER,toneFrequency, TONE_DURATION);
  delay(TONE_DURATION);
  
  noTone(BUZZER);
	
}
int readButtons(){
  if(digitalRead(BUTTON_RED)==LOW){
  return 1;
  }
  if(digitalRead(BUTTON_GREEN)==LOW){
  return 2;
  }
  if(digitalRead(BUTTON_BLUE)==LOW){
  return 3;
  }
  if(digitalRead(BUTTON_YELLOW)==LOW){
  return 4;
  }
  return 0; 

}
void clearLEDs(){

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_YELLOW, LOW);
  
}

void setLEDs(bool red, bool green, bool blue, bool yellow){
  digitalWrite(LED_RED, red ? HIGH:LOW);
  digitalWrite(LED_GREEN,green ? HIGH:LOW);
  digitalWrite(LED_BLUE, blue ? HIGH:LOW);
  digitalWrite(LED_YELLOW, yellow ? HIGH:LOW);
}


  
  
  
