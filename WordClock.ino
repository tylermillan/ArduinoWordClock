/* 
Tyler Millan
University of Oregon
Word Clock Maker Project

*/
#include "Wire.h" 
#define DS3231_I2C_ADDRESS 0x68
#include <Adafruit_NeoPixel.h>

//data pin on arduino 
#define PIN            6

// since we are using a 12 by 12 array 
#define NUMPIXELS     144

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);



byte sec
byte minute
byte hour
byte dayOfWeek
byte dayOfMonth
byte month
byte year

//definition of colors
uint32_t Black = pixels.Color(0,0,0);
uint32_t White = pixels.Color(255,255,255);
uint32_t Green = pixels.Color(0,255,0);
uint32_t Red = pixels.Color(255,0,0);
uint32_t Gold = pixels.Color(255,204,0);
uint32_t Grey = pixels.Color(30,30,30);
uint32_t Blue = pixels.Color(0,0,255);
uint32_t whiteblue = pixels.Color(255,255,255);
uint32_t lightblue = pixels.Color(153,204,255);
uint32_t midblue = pixels.Color(0,102,204);
uint32_t darkblue = pixels.Color(0,0,255);
uint32_t Brown = pixels.Color(153,102,051);
uint32_t Pink = pixels.Color(255,153,153);

byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}

//Actual words as array variables
int WordIts[] = {132, 133, 134, -1};
int WordAbout[] = {136, 137, 138, 139, 140, -1};
int WordTwenty[] = {131, 130, 129, 128, 127, 126, -1};
int WordMinTen[] = {124, 123, 122, -1};
int WordMinFive[] = {108, 109, 110, 111, -1};
int WordQuarter[] = {113, 114, 115, 116, 117, 118, 119, -1};
int WordMinutes[] = {107, 106, 105, 104, 103, 102, 101, -1};
int WordHalf[] = {100, 99, 98, 97, -1};
int WordTo[] = {84, 85, -1};
int WordPast[] = {86, 87, 88, 89, -1};
int WordFive[] = {91, 92, 93, 94, -1};
int WordOne[] = {83, 82, 81, -1};
int WordTwo[] = {80, 79, 78, -1};
int WordThree[] = {77, 76, 75, 74, 73, -1};
int WordFour[] = {60, 61, 62, 63, -1};
int WordSix[] = {64, 65, 66, -1};
int WordSeven[] = {67, 68, 69, 70, 71, -1};
int WordEight[] = {59, 58, 57, 56, 55, -1};
int WordNine[] = {54, 53, 52, 51, -1};
int WordTen[] = {50, 49, 48, -1};
int WordEleven[] = {36, 37, 38, 39, 40, 41, -1};
int WordTwelve[] = {42, 43, 44, 45, 46, 47, -1};
int WordOclock[] = {35, 34, 33, 32, 31, 30, -1};

int WordGoDucks[] = 

int WordTime[] = {28, 27, 26, 25, -1};
int WordFor[] = {12,13,14, -1};
int WordA[] = {16, -1};
int WordBeer[] = {17,18,19,20, -1};

int flag = 0; //used for display effects to stop it showing more than once



//initial setup of clock
void setup()
{
  Wire.begin();
  pixels.begin();
  Serial.begin(9600);
  pinMode(10, INPUT);
  pinMode(8,INPUT);
  blank();
  pixels.setBrightness(255);

test(); 


}

void loop()
{

  TimeOfDay(); 
  displayTime(); 
 
  //home time
  if((dayOfWeek != 1) && (dayOfWeek != 7)) {
    if(hour == 17){
      lightup(WordTime, White);
      lightup(WordFor, White);
      lightup(WordHome, Green);
      }
    else if (hour == 18) {
      lightup(WordTime, White);
      lightup(WordFor, White);
      lightup(WordHome, Red);
     }
   
  else if (hour == 12) {
     // turn off messages
    lightup(WordTime, White);
    lightup(WordFor, White);
    lightup(WordCoffee, Black);
    lightup(WordTea, Black);
    lightup(WordLunch, White);
    }
    //coffee  time
  else if ((minute >=10) && (minute<=15) && (hour > 8) && (hour < 17)) {
      if (hour < 12) {
        lightup(WordTime, White);
        lightup(WordFor, White);
        lightup(WordA, White);
        lightup(WordCoffee, Brown);
        lightup(WordTea, Black);
        lightup(WordLunch, Black);
        lightup(WordHome, Black);
      }
      else {
        // tea time
        lightup(WordTime, White);
        lightup(WordFor, White);
        lightup(WordA, Black);
        lightup(WordCoffee, Black);
        lightup(WordTea, White);
        lightup(WordLunch, Black);
        lightup(WordHome, Black);
      }
    }
  else{
     // turn off messages
    lightup(WordTime, Black);
    lightup(WordFor, Black);
    lightup(WordA, Black);
    lightup(WordCoffee, Black);
    lightup(WordTea, Black);
    lightup(WordLunch, Black);
    lightup(WordHome, Black);
   }
  }

  lightup(WordIts, White);
 
  if((minute == 0)
    |(minute == 5)
    |(minute == 10)
    |(minute == 15)
    |(minute == 20)
    |(minute == 25)
    |(minute == 30)
    |(minute == 35)
    |(minute == 40)
    |(minute == 45)
    |(minute == 50)
    |(minute == 55)){
      lightup(WordAbout, Black);
    }
  else{
      if((minute == 6)
    |(minute == 1)
    |(minute == 11)   
    |(minute == 16)
    |(minute == 21)
    |(minute == 26)
    |(minute == 31)
    |(minute == 36)
    |(minute == 41)
    |(minute == 46)
    |(minute == 51)
    |(minute == 56)){
      lightup(WordAbout, whiteblue);
    }
      else if ((minute == 7)
    |(minute == 2)
    |(minute == 17)
    |(minute == 22)
    |(minute == 27)
    |(minute == 32)
    |(minute == 37)
    |(minute == 42)
    |(minute == 47)
    |(minute == 52)
    |(minute == 57)){
      lightup(WordAbout, lightblue);
    }
     else if ((minute == 8)
    |(minute == 13)
    |(minute == 3)
    |(minute == 18)
    |(minute == 23)
    |(minute == 28)
    |(minute == 33)
    |(minute == 38)
    |(minute == 43)
    |(minute == 48)
    |(minute == 53)
    |(minute == 58)){
      lightup(WordAbout, midblue);
    }
      else if ((minute == 9)
    |(minute == 14)
    |(minute == 4)
    |(minute == 19)
    |(minute == 24)
    |(minute == 29)
    |(minute == 34)
    |(minute == 39)
    |(minute == 44)
    |(minute == 49)
    |(minute == 54)
    |(minute == 59)){
      lightup(WordAbout, darkblue);
    }
      else {
      lightup(WordAbout, White);
        
      }
    
    }

  if((minute >= 0) && (minute < 5)){
    lightup(WordOclock, White);
  }
  else {
    lightup(WordOclock, Black);
  }


  if(minute <35){
  //Set hour if minutes are less than 35
  switch (hour) {
    case 1:
    case 13:
      lightup(WordOne, White);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 2:
    case 14:
      lightup(WordOne, Black);
      lightup(WordTwo, White);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 3:
    case 15:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, White);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 4:
    case 16:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, White);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 5:
    case 17:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, White);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 6:
    case 18:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, White);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 7:
    case 19:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, White);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 8:
    case 20:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, White);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 9:
    case 21:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, White);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 10:
    case 22:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, White);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 11:
    case 23:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, White);
      lightup(WordTwelve, Black);
      break;
    case 00:
    case 12:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, White);
      break;
      }// end of case statement
      if ((minute >= 0) && (minute <5)) {
        lightup(WordPast, Black);
        lightup(WordTo,   Black);
        }
      else {
        lightup(WordPast, White);
        lightup(WordTo,   Black);
        }
       
  }//end of if statement

else if (minute >34) {
 //Set hour if minutes are greater than 34
  switch (hour) {
    case 1:
    case 13:
      lightup(WordOne, Black);
      lightup(WordTwo, White);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 2:
    case 14:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, White);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 3:
    case 15:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, White);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 4:
    case 16:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, White);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 5:
    case 17:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, White);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 6:
    case 18:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, White);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 7:
    case 19:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, White);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 8:
    case 20:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, White);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 9:
    case 21:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, White);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
    case 10:
    case 22:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, White);
      lightup(WordTwelve, Black);
      break;
    case 11:
    case 23:
      lightup(WordOne, Black);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, White);
      break;
    case 00:
    case 12:
      lightup(WordOne, White);
      lightup(WordTwo, Black);
      lightup(WordThree, Black);
      lightup(WordFour, Black);
      lightup(WordFive, Black);
      lightup(WordSix, Black);
      lightup(WordSeven, Black);
      lightup(WordEight, Black);
      lightup(WordNine, Black);
      lightup(WordTen, Black);
      lightup(WordEleven, Black);
      lightup(WordTwelve, Black);
      break;
       }// end of case statement
      lightup(WordPast, Black);
      lightup(WordTo,   White);
    } // end of if statement to test for greater than 34

if ((minute >= 5) && (minute <10)) {
      lightup(WordMinFive, White);
      lightup(WordMinTen, Black);
      lightup(WordQuarter, Black);
      lightup(WordTwenty, Black);
      lightup(WordMinutes, White);
      lightup(WordHalf, Black);
}
else if ((minute >= 10) && (minute <15)) {
      lightup(WordMinFive, Black);
      lightup(WordMinTen, White);
      lightup(WordQuarter, Black);
      lightup(WordTwenty, Black);
      lightup(WordMinutes, White);
      lightup(WordHalf, Black);
}
else if ((minute >= 15) && (minute <20)) {
      lightup(WordMinFive, Black);
      lightup(WordMinTen, Black);
      lightup(WordQuarter, White);
      lightup(WordTwenty, Black);
      lightup(WordMinutes, Black);
      lightup(WordHalf, Black);
}
else if ((minute >= 20) && (minute <25)) {
      lightup(WordMinFive, Black);
      lightup(WordMinTen, Black);
      lightup(WordQuarter, Black);
      lightup(WordTwenty, White);
      lightup(WordMinutes, White);
      lightup(WordHalf, Black);
}
else if ((minute >= 25) && (minute <30)) {
      lightup(WordMinFive, White);
      lightup(WordMinTen, Black);
      lightup(WordQuarter, Black);
      lightup(WordTwenty, White);
      lightup(WordMinutes, White);
      lightup(WordHalf, Black);
}
else if ((minute >= 30) && (minute <35)) {
      lightup(WordMinFive, Black);
      lightup(WordMinTen, Black);
      lightup(WordQuarter, Black);
      lightup(WordTwenty, Black);
      lightup(WordMinutes, Black);
      lightup(WordHalf, White);
}
else if ((minute >= 35) && (minute <40)) {
      lightup(WordMinFive, White);
      lightup(WordMinTen, Black);
      lightup(WordQuarter, Black);
      lightup(WordTwenty, White);
      lightup(WordMinutes, White);
      lightup(WordHalf, Black);
}
else if ((minute >= 40) && (minute <45)) {
      lightup(WordMinFive, Black);
      lightup(WordMinTen, Black);
      lightup(WordQuarter, Black);
      lightup(WordTwenty, White);
      lightup(WordMinutes, White);
      lightup(WordHalf, Black);
}
else if ((minute >= 45) && (minute <50)) {
      lightup(WordMinFive, Black);
      lightup(WordMinTen, Black);
      lightup(WordQuarter, White);
      lightup(WordTwenty, Black);
      lightup(WordMinutes, Black);
      lightup(WordHalf, Black);
}
else if ((minute >= 50) && (minute <55)) {
      lightup(WordMinFive, Black);
      lightup(WordMinTen, White);
      lightup(WordQuarter, Black);
      lightup(WordTwenty, Black);
      lightup(WordMinutes, White);
      lightup(WordHalf, Black);
}
else if ((minute >= 55) && (minute <=59)) {
      lightup(WordMinFive, White);
      lightup(WordMinTen, Black);
      lightup(WordQuarter, Black);
      lightup(WordTwenty, Black);
      lightup(WordMinutes, White);
      lightup(WordHalf, Black);
}
else if ((minute >= 0) && (minute <5)) {
      lightup(WordMinFive, Black);
      lightup(WordMinTen, Black);
      lightup(WordQuarter, Black);
      lightup(WordTwenty, Black);
      lightup(WordMinutes, Black);
      lightup(WordHalf, Black);

}

}

void TimeOfDay() {
//Used to set brightness dependant of time of day - lights dimmed at night

//monday to thursday and sunday

if ((dayOfWeek == 6) | (dayOfWeek == 7)) {
  if ((hour > 0) && (hour < 8)) {
    pixels.setBrightness(5);
  }
  else {
    pixels.setBrightness(200);
  }
}
else {
  if ((hour < 6) | (hour >=22)) {
    pixels.setBrightness(5);
  }
  else {
    pixels.setBrightness(200);
  }
}
}

void displayTime()
{
// retrieve data from DS3231
readtime(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

int minbutton = digitalRead(10);
int hourbutton = digitalRead(8);

if ((minbutton == HIGH) && (hourbutton == HIGH)) {

  test();

}


if (minbutton == HIGH) {
  Serial.println("Minute button pressed");
  if (minute >54) {
    minute = 0;
    }
  else {
    minute = minute + 1;
    }
    settime(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
  }
  
if (hourbutton == HIGH) {
  Serial.println("Hour button pressed");
    if (hour != 23) {
      hour = hour + 1; 
    }
    else {
      hour = 0;
    }  
    settime(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
    }

if (hour < 10) {
  Serial.print("0");
}
Serial.print(hour);
Serial.print(":");

if (minute < 10) {
   Serial.print("0");
}
Serial.println(minute);
delay(200);

}

void settime(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year) {
 
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}

void readtime(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year) {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

void lightup(int Word[], uint32_t Colour) {
for (int x = 0; x < pixels.numPixels() + 1; x++) {
  if(Word[x] == -1) {
    pixels.show();
    break;
  } //end of if loop
  else {
    pixels.setPixelColor(Word[x], Colour);
    pixels.show();
  } // end of else loop
} //end of for loop
}

void blank() {
//clear the decks
for (int x = 0; x < NUMPIXELS; ++x) {
  pixels.setPixelColor(x, Black);
}
  pixels.show();

}

void wipe() {

  for (int x = 0; x < NUMPIXELS; ++x) {
    pixels.setPixelColor(x, Blue);
    delay(10);
    pixels.show();
    }
  delay(50);  
  for (int x = NUMPIXELS; x > -1; --x) {
    pixels.setPixelColor(x, Black);
    delay(10);
    pixels.show();
  }
  
   for (int x = 0; x < NUMPIXELS; ++x) {
    pixels.setPixelColor(x, Green);
    delay(10);
    pixels.show();
    }
  delay(50);  
  for (int x = NUMPIXELS; x > -1; --x) {
    pixels.setPixelColor(x, Black);
    delay(10);
    pixels.show();
  }
  
   for (int x = 0; x < NUMPIXELS; ++x) {
    pixels.setPixelColor(x, Red);
    delay(10);
    pixels.show();
   }
  delay(50);  
  for (int x = NUMPIXELS; x > -1; --x) {
    pixels.setPixelColor(x, Black);
    delay(10);
    pixels.show();
  }

  for (int x = 0; x < NUMPIXELS; x=x+2) {
    pixels.setPixelColor(x, Red);
    delay(50);
    pixels.show();
   }
   delay(1000);
  blank();

}

void startupsequence() {
blank();
wipe();
blank();
flash(); 
}

void flash() {

blank();
for (int y = 0; y< 10; ++y) {
    for (int x = 0; x < NUMPIXELS; x=x+2) {
      pixels.setPixelColor(x, Pink);
    }
    pixels.setBrightness(200);
    pixels.show();
    delay(50);
    blank();
    delay(50);

    for (int x = 1; x < NUMPIXELS; x=x+2) {
      pixels.setPixelColor(x, Pink);  
    }
    pixels.setBrightness(200);
    pixels.show();
    delay(50);
    blank();
    delay(50);
}
blank();
}
