// NB: ALL NOTES DEFINED WITH STANDARD ENGLISH NAMES, EXCEPT FROM "A" 
//THAT IS CALblue  WITH THE ITALIAN NAME "LA" BECAUSE A0,A1...ARE THE ANALOG PINS ON ARDUINO.
// (Ab IS CALblue  Ab AND NOT LAb)
#define C0 16.35
#define Db0 17.32
#define D0  18.35
#define Eb0 19.45
#define E0  20.60
#define F0  21.83
#define Gb0 23.12
#define G0  24.50
#define Ab0 25.96
#define LA0 27.50
#define Bb0 29.14
#define I0  30.87
#define C1  32.70
#define Db1 34.65
#define D1  36.71
#define Eb1 38.89
#define E1  41.20
#define F1  43.65
#define Gb1 46.25
#define G1  49.00
#define Ab1 51.91
#define LA1 55.00
#define Bb1 58.27
#define I1  61.74
#define C2  65.41
#define Db2 69.30
#define D2  73.42
#define Eb2 77.78
#define E2  82.41
#define F2  87.31
#define Gb2 92.50
#define G2  98.00
#define Ab2 103.83
#define LA2 110.00
#define Bb2 116.54
#define I2  123.47
#define C3  130.81
#define Db3 138.59
#define D3  146.83
#define Eb3 155.56
#define E3  164.81
#define F3  174.61
#define Gb3 185.00
#define G3  196.00
#define Ab3 207.65
#define LA3 220.00
#define Bb3 233.08
#define I3  246.94
#define C4  261.63
#define Db4 277.18
#define D4  293.66
#define Eb4 311.13
#define E4  329.63
#define F4  349.23
#define Gb4 369.99
#define G4  392.00
#define Ab4 415.30
#define LA4 440.00
#define Bb4 466.16
#define I4  493.88
#define C5  523.25
#define Db5 554.37
#define D5  587.33
#define Eb5 622.25
#define E5  659.26
#define F5  698.46
#define Gb5 739.99
#define G5  783.99
#define Ab5 830.61
#define LA5 880.00
#define Bb5 932.33
#define I5  987.77
#define C6  1046.50
#define Db6 1108.73
#define D6  1174.66
#define Eb6 1244.51
#define E6  1318.51
#define F6  1396.91
#define Gb6 1479.98
#define G6  1567.98
#define Ab6 1661.22
#define LA6 1760.00
#define Bb6 1864.66
#define I6  1975.53
#define C7  2093.00
#define Db7 2217.46
#define D7  2349.32
#define Eb7 2489.02
#define E7  2637.02
#define F7  2793.83
#define Gb7 2959.96
#define G7  3135.96
#define Ab7 3322.44
#define LA7 3520.01
#define Bb7 3729.31
#define B7  3951.07
#define C8  4186.01
#define Db8 4434.92
#define D8  4698.64
#define Eb8 4978.03

const byte PIN_BUZZER = 10;
const byte PIN_BTN1 = 2;
const byte PIN_BTN2 = 3;
const byte PIN_BTN3 = 4;
const byte PIN_BTN4 = 5;
const byte PIN_BTN5 = 6;
const byte PIN_BTN6 = 7;
const byte PIN_BTN7 = 8;
const byte PIN_BTN8 = 9;

const byte PIN_H = A1;
const byte PIN_V = A0;
const byte PIN_SW = 12;

const byte led_red=13;
const byte led_green = A4;
const byte led_blue = A5;

int color[3];

float frequency[8] = { C4, D5, E5, F6, G6, LA7, B7, C8 };

void setup() {
  Serial.begin(9600); // Opens Serial communication
  
  // pin rgb
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_blue, OUTPUT);

  // pin buzzer
  pinMode(PIN_BUZZER, OUTPUT);

  // pin button
  pinMode(PIN_BTN1, INPUT_PULLUP);
  pinMode(PIN_BTN2, INPUT_PULLUP);
  pinMode(PIN_BTN3, INPUT_PULLUP);
  pinMode(PIN_BTN4, INPUT_PULLUP);
  pinMode(PIN_BTN5, INPUT_PULLUP);
  pinMode(PIN_BTN6, INPUT_PULLUP);
  pinMode(PIN_BTN7, INPUT_PULLUP);
  pinMode(PIN_BTN8, INPUT_PULLUP);
  
  // analog
  pinMode(PIN_V, INPUT);
  analogWrite(PIN_BUZZER,0);
}

void setColor(int red, int green, int blue) {
  int i=0;
  for(i; i<(sizeof(color)/ sizeof(color[0]));i++){ 
    Serial.print(i);
    Serial.print("--- ");
    Serial.println(color[i]);
  }
  
  #ifdef COMMON_ANODE 
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
  #endif 
  analogWrite(led_red, red);
  analogWrite(led_blue, blue);
  analogWrite(led_green, green);

  color[0] = red;
  color[1] = green;
  color[2] = blue;
}

void manageColor(int position, int nombre){ 
  float croix = (nombre / 10)+100;
  //Serial.print(nombre);
  //Serial.print("------------");
  //Serial.println(croix);
  
  switch(position){
    case 1:
      if(croix+color[0]>255){
        croix = 255;
      } else if (croix<150){
        croix += 50;
      };
      setColor(croix, color[1], color[2]);
      break;
    case 2:
      if(croix+color[1]>255){
        croix = 255;
      } else if (croix<150){
        croix += 50;
      };
      setColor(color[0], croix, color[2]);
      break;
  }
}

void wahwah(float frequence){
  if(analogRead(PIN_V)<520 && analogRead(PIN_V)>515){
    setColor(0, 0, 250);
    tone(PIN_BUZZER,frequence);
  }
  if(analogRead(PIN_V)<515) {
    manageColor(1, analogRead(PIN_V));
    int newfreq = frequence+analogRead(PIN_V);
    tone(PIN_BUZZER,newfreq);
  }
  if(analogRead(PIN_V)>520) {
    manageColor(2, analogRead(PIN_V));
    int newfreq = frequence+1000+analogRead(PIN_V);
    tone(PIN_BUZZER,newfreq);
  }
}

void loop() {
  if(digitalRead(PIN_BTN1)==LOW)
  {
    while(digitalRead(PIN_BTN1)==LOW){
      Serial.println(color[0]);
      Serial.println(color[1]);
      Serial.println(color[2]);
      wahwah(frequency[0]);
    }
  }
  
  else if(digitalRead(PIN_BTN2)==LOW)
  {
    while(digitalRead(PIN_BTN2)==LOW){
      wahwah(frequency[1]);
    }
  }
  
  else if(digitalRead(PIN_BTN3)==LOW)
  {
    while(digitalRead(PIN_BTN3)==LOW){
      wahwah(frequency[2]);
    }
  }
  
  else if(digitalRead(PIN_BTN4)==LOW)
  {
    while(digitalRead(PIN_BTN4)==LOW){
      wahwah(frequency[3]);
    }
  }
  
  else if(digitalRead(PIN_BTN5)==LOW)
  {
    while(digitalRead(PIN_BTN5)==LOW){
      wahwah(frequency[4]);
    }
  }
  
  else if(digitalRead(PIN_BTN6)==LOW)
  {
    while(digitalRead(PIN_BTN6)==LOW){
      wahwah(frequency[5]);
    }
  }
  
  else if(digitalRead(PIN_BTN7)==LOW)
  {
    while(digitalRead(PIN_BTN7)==LOW){
      wahwah(frequency[6]);
    }
  }
  
  else if(digitalRead(PIN_BTN8)==LOW)
  {
    while(digitalRead(PIN_BTN8)==LOW){
      wahwah(frequency[7]);
    }
  } else {
    setColor(0, 0, 0);
  }
  
  noTone(PIN_BUZZER);
  delay(10); //reading delay
}
