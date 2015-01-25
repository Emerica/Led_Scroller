#define USB_CFG_DEVICE_NAME     'W','B'
#define USB_CFG_DEVICE_NAME_LEN 2
#include <DigiUSB.h>
#include "IRremote.h"            
IRsend irsend;       
void setup()
{
 DigiUSB.begin();
}
char codes[] = { 0xFFF807,0xFFBA45,0xFFFA05,0xFF38C7,
                0xFF3AC5,0xFF7887,0xFF7A85,0xFFB847,
                0xFF1AE5,0xFF58A7,0xFFDA25,0xFF9867,
                0xFFD827,0xFF9A65,0xFF5AA5,0xFF18E7,
                0xFFC03F,0xFF40BF,0xFFC23D,0xFF807F,
                0xFF02FD,0xFF827D,0xFF42BD,0xFF00FF,
                0xFF22DD,0xFF609F,0xFF629D,0xFF20DF,
                0xFFE01F,0xFFA25D,0xFFE21D,0xFFA05F,
                0xFF50AF,0xFF52AD,0xFF906F,
                0xFFD02F,0xFF926D,0xFF10EF,
                0xFF12ED,0xFFD22D,0xFFB04F,
                0xFF0AF5,0xFF8A75,0xFFCA35,0xFF8877,
                0xFFC837,0xFF48B7,0xFF4AB5,0xFF08F7,
                0xFFE817,0xFFAA55,0xFFEA15,0xFF28D7
              }; 

char keys[] = { '`','a','b','`',
                'c','d','e','f',
                'g','h','i','j',
                'k','l','m','n',
                'o','p','q','r',
                's','t','u','v',
                'w','x','y','z',
                '!','?','#','$',
                '`','`','`',
                '`','`','`',
                '`','`','`',
                '1','2','3','4',
                '5','6','7','8',
                '`','9','0','`'
              };



void writechar(char str){
  irsend.sendNEC(getindex(str),32);
}

long getindex(char key){
  delay(1000);
  for(int i=0; i< 54; i++){
     if(keys[i] == key){
       return codes[i];
     }
  }
}

char s;
int sent;
int first=0;
void loop() {
  DigiUSB.refresh();
  digitalWrite(1,LOW);
  if (DigiUSB.available() > 0) {
    digitalWrite(1,HIGH);
    s = DigiUSB.read();
    if(!first){
      //First char is the slot to edit.
      //Send edit
      irsend.sendNEC(0xFF926D,32);//EDT
      delay(100);
      writechar(s);//SLOT
      delay(100);
      irsend.sendNEC(0xFF12ED,32);//ENT
      delay(100);
      irsend.sendNEC(0xFFB04F,32);//CLR
      delay(100);
      irsend.sendNEC(0xFF629D, 32);
      delay(100);
      first=1;
    }else if (s == '\n') {
        irsend.sendNEC(0xFF12ED,32); 
        first=0;
    } else {  
        writechar(s);
    }
  }
  //delay(1000);
}
