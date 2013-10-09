#include <LedControl.h>

//We always have to include the library

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
String val; // Data received from the serial port

int devNum = 8;
int intensity = 1;
LedControl lc=LedControl(12,11,10,devNum);

/* we always wait a bit between updates of the display */
unsigned long delaytime=1;

int pos [] = {
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,
  42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,
81,82,83,84,85,86,87};
int posLen = 88;


/*
byte a[64]={
  B0,B1111110,B10010,B10010,B10,B0,
  B1001000,B1111010,B1000000,B0,
  B1000010,B1111110,B1000000,B0,
  B1001000,B1111010,B1000000,B0,
  B1111110,B10000,B101000,B1000100,B0,
  B100000,B1010100,B1010100,B1111000,B0,B0,
  B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,
  B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0,B0
};*/

byte a[88] = {
  B00111100,B1000010,B1010010,B110100,B0,
  B1001000,B1111010,B1001000,B0,
  B10,B10,B1111110,B10,B10,B0,
  B10,B10,B1111110,B10,B10,B0,
  B1001000,B1111010,B1001000,B0,
  B111000,B1000101,B1010101,B110000,B0,
  B1001000,B1111010,B1001000,B0,
  B0,B0,B0,
  B10,B100,B1111000,B100,B10,B0,
  B1111110,B1001010,B1001010,B0,
  B1111110,B11010,B101010,B1000100,B0,
  B1111110,B1001010,B1001010,B0,
  B0,B0,B0,
  B1111110,B10000,B101000,B1000100,B0,
  B1111100,B10010,B10010,B1111100,B0,
  B1111110,B1000010,B1000010,B111100,B0,
  B1111100,B10010,B10010,B1111100,B0,
  B1111110,B11010,B101010,B1000100,B0,
  B0,B0,B0
};




void setup() {

  clearAllScreens();

}


void clearAllScreens() {
  //we have already set the number of devices when we created the LedControl
  int devices=lc.getDeviceCount();
  //we have to init all devices in a loop
  for(int address=0;address<devices;address++) {
    /*The MAX72XX is in power-saving mode on startup*/
    lc.shutdown(address,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(address,intensity);
    /* and clear the display */
    lc.clearDisplay(address);

  } 


}



void BlinkScreen()
{

  placeCharsOnMatrix();

  delay(1000);
  clearAllScreens();
  delay(1000);

  placeCharsOnMatrix();

  delay(1000);
  clearAllScreens();
  delay(1000);

  placeCharsOnMatrix();

  delay(1000);
}


void writeArduinoOnMatrix() {

  placeCharsOnMatrix();

  // Change array order to scroll text right to left
  for (int i=0; i < posLen; i++)
  {   
    pos[i] = pos[i] + 1;
    if(pos[i] > posLen -1)
    {
      pos[i] = 0;
    }
  }
  
  delay(delaytime);


}

void placeCharsOnMatrix() {


  // For the first Dot Matrix
  for (int j=0; j < devNum; j++)
  {
    for (int i=0; i < 8; i++)
    {   
      lc.setRow(j,7-((i+8*j) % 8),a[pos[i+8*j]]); 
      //lc.setLed(j,7-((i+8*j) % 8),a[pos[i+8*j]],true);
      
    }
  }


  /*
  
   for (int i=0; i < 8; i++)
   {   
   lc.setRow(0,7-i,a[pos[i]]); 
   }
   
   // For the second Dot Matrix
   for (int i=8; i < 16; i++)
   {         
   lc.setRow(1,7-(i % 8),a[pos[i]]);      
   }
   
   
   // For the third Dot Matrix
   for (int i=16; i < 24; i++)
   {         
   lc.setRow(2,7-(i % 8),a[pos[i]]);      
   } 
   
   // For the fourth Dot Matrix
   for (int i=24; i < 32; i++)
   {         
   lc.setRow(3,7-(i % 8),a[pos[i]]);      
   } 
   
   // For the fifth Dot Matrix
   for (int i=32; i < 40; i++)
   {         
   lc.setRow(4,7-(i % 8),a[pos[i]]);      
   } 
   
   // For the 6th Dot Matrix
   for (int i=40; i < 48; i++)
   {         
   lc.setRow(5,7-(i % 8),a[pos[i]]);      
   } 
   
   // For the 7th Dot Matrix
   for (int i=48; i < 56; i++)
   {         
   lc.setRow(6,7-(i % 8),a[pos[i]]);      
   } 
   
   // For the 8th Dot Matrix
   for (int i=56; i < 64; i++)
   {         
   lc.setRow(7,7-(i % 8),a[pos[i]]);      
   } 
   */
}



void rows() {
  for (int i = 0; i < 8; i++) {
    for(int row=0;row<8;row++) {
      delay(50);
      lc.setRow(i,7-(row % 8),B11111111);
    }
  }
}

void loop() { 
  /*
  if(pos[0] == 0)
   {
   rows(); 
   //BlinkScreen();
   delay(10);
   for (int i = 0; i < 8; i++) {
   for(int row=0;row<8;row++) {
   delay(10);
   lc.setRow(i,7-(row % 8),B00000000);
   }
   }
   }*/


  writeArduinoOnMatrix();
  /*
  //
   for (int row=0; row<8; row++)
   {
   for (int col=0; col<8; col++)
   {
   lc.setLed(0,col,row,true); // turns on LED at col, row
   delay(10);
   lc.setLed(0,col,row,false); // turns off LED at col, row
   delay(10);
   }
   }
   
   */
}




