#include <IRremote.h>

IRsend irsend;

String keystring = "abcdefghijklmnopqrstuvwxyz";
String capskeystring = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
String symbols = "@%^&*-_()+=[]:/\\;\"`'.,<>{}!?#$}";
String numeric = "1234567890";

              
long alphacodes[] = { 
                      0xFFBA45,0xFFFA05,
                      0xFF3AC5,0xFF7887,0xFF7A85,0xFFB847,
                      0xFF1AE5,0xFF58A7,0xFFDA25,0xFF9867,
                      0xFFD827,0xFF9A65,0xFF5AA5,0xFF18E7,
                      0xFFC03F,0xFF40BF,0xFFC23D,0xFF807F,
                      0xFF02FD,0xFF827D,0xFF42BD,0xFF00FF,
                      0xFF22DD,0xFF609F,0xFF629D,0xFF20DF,
                      0xFFE01F,0xFFA25D,0xFFE21D,0xFFA05F,
                    }; 
                    
long numcodes[] = {0xFF0AF5,0xFF8A75,0xFFCA35,0xFF8877,
                      0xFFC837,0xFF48B7,0xFF4AB5,0xFF08F7,
                      0xFFAA55,0xFFEA15
                    };


void setup()
{
  Serial.begin(9600);
}

void cap(){
  irsend.sendNEC(0xFF906F, 32);
  delay(50);
}

void shift(){
  irsend.sendNEC(0xFF50AF, 32);
  delay(50);
}

void power(){
  irsend.sendNEC(0xFF38C7, 32);
}

void edit(){
  irsend.sendNEC(0xFF926D, 32);
  delay(50);
}

void enter(){
  irsend.sendNEC(0xFF12ED, 32);
  delay(50);
}
void run(){
  irsend.sendNEC(0xFFF807, 32);
  delay(50);
}
void cleartext(){
  irsend.sendNEC(0xFFB04F, 32);
  delay(50);
}

void editslot(char slot){
  edit();
  writechar(slot);
  enter();
  cleartext();
  writechar('y');
  delay(1000);
}

void save(){
  delay(1000);
  enter();
}


void writechar(char key){
  
  int index = 0;
  if(key == ' '){
    irsend.sendNEC(0xFF10EF,32);
  }
  index = keystring.indexOf(key);
  if(index>=0){
     irsend.sendNEC(alphacodes[index],32);
  } 
  index= capskeystring.indexOf(key);
  if(index>=0){
     cap();
     irsend.sendNEC(alphacodes[index],32);
     cap();
  }
  index = symbols.indexOf(key);
  if(index>=0){
     shift();
     irsend.sendNEC(alphacodes[index],32);
  }
  index = numeric.indexOf(key);
  if(index>=0){
     irsend.sendNEC(numcodes[index],32);
  }
  //delay(10);
}


char s;
int first = 0;
void loop() {
  if(Serial.available() > 0) {
    s = Serial.read();
    if(!first){
      if(s==0x72){
        run();
        s = Serial.read();
        writechar(s); 
        enter();
        first = 0;
      }else{
        editslot(s);
        first = 1;
      }
    }else if( s == 0x0a){
       enter();
       first = 0;
    }else{
      Serial.print(s);
     writechar(s); 
    }
  }
  
}
