#include <UTFT.h>
#include <URTouch.h>

UTFT  LCD(ILI9341_16,38,39,40,41);

URTouch  touch( 6, 5, 4, 3, 2);

// Declare which fonts we will be using
extern uint8_t BigFont[];
extern uint8_t SmallFont[];

#define stp 9
#define dir 8

/*************************
**   Custom functions   **
*************************/

int timePassed;
long long h=0, m=0, s = 0, adj = 0;
int yr = 2023, mo = 5, d = 20;
int page = 1;
int x, y;
bool ok = true;
long long nr=0;
int tr1 = -1, tr2 = -1, tr3 = -1, tr4 = -1;
int difh, difm, difs;


void calcMonth(int ian, int feb, int mar, int apr, int may, int iul, int iun, int aug, int sep, int oct, int nov, int dec) {
  switch (mo) {
      case 1:
      if (d > ian) {
        d = 1;
        mo ++;
      }
      break;
      case 2:
      if (d > feb) {
        d = 1;
        mo ++;
      }
      break;
      case 3:
      if (d > mar) {
        d = 1;
        mo ++;
      }
      break;
      case 4:
      if (d > apr) {
        d = 1;
        mo ++;
      }
      break;
      case 5:
      if (d > may) {
        d = 1;
        mo ++;
      }
      break;
      case 6:
      if (d > iun) {
        d = 1;
        mo ++;
      }
      break;
      case 7:
      if (d > iul) {
        d = 1;
        mo ++;
      }
      break;
      case 8:
      if (d > aug) {
        d = 1;
        mo ++;
      }
      break;
      case 9:
      if (d > sep) {
        d = 1;
        mo ++;
      }
      break;
      case 10:
      if (d > oct) {
        d = 1;
        mo ++;
      }
      break;
      case 11:
      if (d > nov) {
        d = 1;
        mo ++;
      }
      break;
      case 12:
      if (d > dec) {
        d = 1;
        mo = 1;
        yr ++;
      }
      break;  
    }  
}

void calcDate(){
  if (yr % 400 == 0) {
    calcMonth(31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
  } else if (yr & 100 == 0) {
    calcMonth(31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
  } else if (yr % 4 == 0) {
    calcMonth(31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
  } else {
    calcMonth(31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
  }
}

void calcTime() {
  s = millis()/1000 - adj;
}

void updateTime() {
  if (s > 59) {
    s = 0;
    adj += 60;
    if (m < 59)
      m ++;
    else {
      m = 0;
      if (h < 23)
        h++;
      else {
        h = 0;
        d ++;
      }
    }
  }
}

void printTime() {
  LCD.setBackColor(0, 0, 0);
  LCD.setColor(255, 255, 255);
  LCD.setFont(BigFont);
  if (h < 10) {
    LCD.printNumI(0, 100, 20);
    LCD.printNumI(h, 120, 20);
  } else {
    LCD.printNumI(h, 101, 20);
  }
  LCD.print(":", 140, 20);
  if (m < 10) {
    LCD.printNumI(0, 160, 20);
    LCD.printNumI(m, 180, 20);
  } else {
    LCD.printNumI(m, 161, 20);
  }
  /*LCD.print(":", 200, 20);
  if (s < 10) {
    LCD.printNumI(0, 220, 20);
    LCD.printNumI(s, 240, 20);
  } else {
    LCD.printNumI(s, 221, 20);
  }*/
}

void printDate() {
  LCD.setBackColor(0, 0, 0);
  LCD.setColor(255, 255, 255);
  LCD.setFont(BigFont);
  if (d < 10) {
    LCD.printNumI(0, 100, 60);
    LCD.printNumI(d, 120, 60);
  } else {
    LCD.printNumI(d, 101, 60);
  }
  switch (mo) {
    case 1:
    LCD.print("Ian", 147, 60);
    break;
    case 2:
    LCD.print("Feb", 147, 60);
    break;
    case 3:
    LCD.print("Mar", 147, 60);
    break;
    case 4:
    LCD.print("Apr", 147, 60);
    break;
    case 5:
    LCD.print("Mai", 147, 60);
    break;
    case 6:
    LCD.print("Iun", 147, 60);
    break;
    case 7:
    LCD.print("Iul", 147, 60);
    break;
    case 8:
    LCD.print("Aug", 147, 60);
    break;
    case 9:
    LCD.print("Sep", 147, 60);
    break;
    case 10:
    LCD.print("Oct", 147, 60);
    break;
    case 11:
    LCD.print("Nov", 147, 60);
    break;
    case 12:
    LCD.print("Dec", 147, 60);
    break;
  }
    LCD.printNumI(yr, 210, 60);
}

void drawHomeScreen() {
  LCD.setBackColor(0, 0, 0);
  LCD.setColor(255, 255, 255);
  LCD.setFont(BigFont);
  LCD.print("ORA:", LEFT, 20);
  LCD.print("DATA:", LEFT, 60);
  LCD.print("PASTILA IN:", LEFT, 100);

  LCD.setColor(255, 255, 255);
  LCD.fillRect(0, 130, 319, 170);
  LCD.fillRect(0, 190, 319, 230); 
  
  LCD.setColor(0, 0, 0);
  LCD.setBackColor(255, 255, 255);
  LCD.print("ADAUGA PASTILA", CENTER, 143);
  LCD.print("SETARI", CENTER, 203);
}

void drawSettingsPage() {
  LCD.setColor(255, 255, 255);
  LCD.fillRect(20, 50, 300, 100);
  LCD.fillRect(20, 140, 300, 190); 

  LCD.setColor(0, 0, 0);
  LCD.setFont(BigFont);
  LCD.setBackColor(255, 255, 255);
  LCD.print("ACTUALIZEAZA ORA", CENTER, 68);
  LCD.print("ACTUALIZEAZA DATA", CENTER, 158);
}

void drawInputScreen() {
  LCD.setColor(255, 255, 255);
  LCD.fillRect(7, 75, 62, 120);
  LCD.fillRect(70, 75, 125, 120); 
  LCD.fillRect(133, 75, 188, 120);
  LCD.fillRect(196, 75, 251, 120); 
  LCD.fillRect(259, 75, 314, 120);
  LCD.fillRect(7, 130, 62, 175);
  LCD.fillRect(70, 130, 125, 175); 
  LCD.fillRect(133, 130, 188, 175);
  LCD.fillRect(196, 130, 251, 175); 
  LCD.fillRect(259, 130, 314, 175);
  LCD.fillRect(7, 185, 155, 230);
  LCD.fillRect(163, 185, 311, 230);

  LCD.setBackColor(255, 255, 255);
  LCD.setFont(BigFont);
  LCD.setColor(0, 0, 0);
  LCD.print("1", 28, 90);
  LCD.print("2", 90, 90);
  LCD.print("3", 153, 90);
  LCD.print("4", 215, 90);
  LCD.print("5", 280, 90);
  LCD.print("6", 28, 145);
  LCD.print("7", 90, 145);
  LCD.print("8", 153, 145);
  LCD.print("9", 215, 145);
  LCD.print("0", 280, 145);
  LCD.print("CLEAR", 200, 200);
  LCD.print("ENTER", 44, 200);
}

void calcInputScreen(int poz) {
  while(true) {
    if(touch.dataAvailable()) {
      delay(100);
      touch.read();
      x = touch.getX();
      y = touch.getY();
      if (x >= 7 && y >= 75 && x <= 62 && y <= 120) {
        nr = nr*10+1;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 70 && y >= 75 && x <= 125 && y <= 120) {
        nr = nr*10+2;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 133 && y >= 75 && x <= 188 && y <= 120) {
        nr = nr*10+3;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 196 && y >= 75 && x <= 251 && y <= 120) {
        nr = nr*10+4;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 259 && y >= 75 && x <= 314 && y <= 120) {
        nr = nr*10+5;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 7 && y >= 130 && x <= 62 && y <= 175) {
        nr = nr*10+6;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 70 && y >= 130 && x <= 125 && y <= 175) {
        nr = nr*10+7;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 133 && y >= 130 && x <= 188 && y <= 175) {
        nr = nr*10+8;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 196 && y >= 130 && x <= 251 && y <= 175) {
        nr = nr*10+9;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 259 && y >= 130 && x <= 314 && y <= 175) {
        nr = nr*10+0;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 7 && y >= 185 && x <= 155 && y <= 230) {
        LCD.fillRect(0, 20, 319, 40);
        break;
      }
      if (x >= 163 && y >= 185 && x <= 311 && y <= 230) {
        nr = 0;
        LCD.fillRect(0, 20, 319, 40);
      }
    }
  }
}

void calcInputScreen1(int poz) {
  while(true) {
    if(touch.dataAvailable()) {
      delay(100);
      touch.read();
      x = touch.getX();
      y = touch.getY();
      if (x >= 7 && y >= 75 && x <= 62 && y <= 120) {
        nr = nr*10+1;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 70 && y >= 75 && x <= 125 && y <= 120) {
        nr = nr*10+2;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 133 && y >= 75 && x <= 188 && y <= 120) {
        nr = nr*10+3;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 196 && y >= 75 && x <= 251 && y <= 120) {
        nr = nr*10+4;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 259 && y >= 75 && x <= 314 && y <= 120) {
        nr = nr*10+5;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 7 && y >= 130 && x <= 62 && y <= 175) {
        nr = nr*10+6;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 70 && y >= 130 && x <= 125 && y <= 175) {
        nr = nr*10+7;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 133 && y >= 130 && x <= 188 && y <= 175) {
        nr = nr*10+8;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 196 && y >= 130 && x <= 251 && y <= 175) {
        nr = nr*10+9;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 259 && y >= 130 && x <= 314 && y <= 175) {
        nr = nr*10+0;
        LCD.printNumI(nr, LEFT, poz);
      }
      if (x >= 7 && y >= 185 && x <= 155 && y <= 230) {
        LCD.fillRect(0, 20, 319, 40);
        break;
      }
      if (x >= 163 && y >= 185 && x <= 311 && y <= 230) {
        nr = 0;
        LCD.fillRect(0, 40, 319, 60);
      }
    }
  }
}

void step2() {
    drawInputScreen();
    if (tr1 == -1) {
      LCD.print("Introdu ORA", CENTER, 0);
      LCD.print("pt PASTILA", CENTER, 20);
      calcInputScreen1(40);
      tr1 = nr;
      nr = 0;
      page = 1;
      ok = 1;
      for(int i=1; i<=200; i++){
        digitalWrite(9, HIGH);
        delay(1);
        digitalWrite(9, LOW);
      }
    } else if (tr2 == -1) {
      LCD.print("Introdu ORA", CENTER, 0);
      LCD.print("pt PASTILA", CENTER, 20);
      calcInputScreen1(40);
      tr2 = nr;
      nr = 0;
      page = 1;
      ok = 1;
      for(int i=1; i<=200; i++){
        digitalWrite(9, HIGH);
        delay(1);
        digitalWrite(9, LOW);
      }
    } else if (tr3 == -1) {
      LCD.print("Introdu ORA", CENTER, 0);
      LCD.print("pt PASTILA", CENTER, 20);
      calcInputScreen1(40);
      tr3 = nr;
      nr = 0;
      page = 1;
      ok = 1;
      for(int i=1; i<=200; i++){
        digitalWrite(9, HIGH);
        delay(1);
        digitalWrite(9, LOW);
      }
    } else if (tr4 == -1) {
      LCD.print("Introdu ORA", CENTER, 0);
      LCD.print("pt PASTILA", CENTER, 20);
      calcInputScreen1(40);
      tr4 = nr;
      nr = 0;
      page = 1;
      ok = 1;
    } 
}

void fullError() {
    LCD.setColor(255, 0, 0);
    LCD.clrScr();
    LCD.print("DISPENSER PLIN!", CENTER, 120);
    delay(700);
    LCD.clrScr();
    delay(100);
    LCD.print("DISPENSER PLIN!", CENTER, 120);
    delay(700);
    LCD.clrScr();
    delay(100);
    LCD.print("DISPENSER PLIN!", CENTER, 120);
    delay(700);
    LCD.clrScr();
    page = 1;
    ok = 1;
}

int startv, sem = 0, sem1 = 0, adj2 = 0;

void timer() {
  if (tr1 != -1) {
    if (tr1 < h)
      tr1 += 24;
    if (tr1 == h)
      tr1++;
    if (sem == 0){
      difh = tr1-h;
      difm -= m;
      sem = 1;
    }
    difs = adj2-s;
    if(s==0)
    adj2 = 0;
    if(difs < 0) {
      adj2 = 60;
      difm--;
    }
    if (difm < 0) {
      difm += 60;
      difh--;
    }
  if (difm == difs && difh == difm && difh == 0) {
    for(int i=1; i<=200; i++){
        digitalWrite(9, HIGH);
        delay(1);
        digitalWrite(9, LOW);
    }\
    tr1 = tr2;
    tr2 = tr3;
    tr3 = tr4;
    tr4 = -1;
    sem = 0;
  }
  LCD.setBackColor(0, 0, 0);
  LCD.setColor(255, 255, 255);
  LCD.setFont(BigFont);
  if (difh < 10) {
    LCD.printNumI(0, 200, 100);
    LCD.printNumI(difh, 220, 100);
  } else {
    LCD.printNumI(difh, 201, 100);
  }
  LCD.print(":", 240, 100);
  if (difm < 10) {
    LCD.printNumI(0, 260, 100);
    LCD.printNumI(difm, 280, 100);
  } else {
    LCD.printNumI(difm, 261, 100);
  }
  } else {
    LCD.setBackColor(0, 0, 0);
    LCD.setColor(255, 255, 255);
    LCD.setFont(SmallFont);
    LCD.print("DISPENSER GOL", 190, 102);
}
}

/*************************
**  Required functions  **
*************************/

void setup()
{
// Initial setup
  LCD.InitLCD();
  LCD.clrScr();

  touch.InitTouch();
  touch.setPrecision(PREC_MEDIUM);

  Serial.begin(9600);
  
  timePassed = millis()/1000;

  pinMode(8,OUTPUT);
  pinMode(9, OUTPUT);

  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void loop(){
  calcTime();
  updateTime();
  calcDate();
  if (page == 1) {
    printTime();
    printDate();
    timer();
    if (ok == 1) {
    drawHomeScreen();
    ok = 0;
    }
    if (touch.dataAvailable()) {
      touch.read();
      x = touch.getX();
      y = touch.getY();
      if (x >= 0 && y >= 130 && x <= 319 && y <= 170 && (tr1 == -1 || tr2 == -1 || tr3 == -1 || tr4 == -1)) {
        page = 2;
        LCD.clrScr();
      } else if (x >= 0 && y >= 130 && x <= 319 && y <= 170 && !(tr1 == -1 || tr2 == -1 || tr3 == -1 || tr4 == -1)) {
        fullError();
      }
      if (x >= 0 && y >= 190 && x <= 319 && y <= 230) {
        LCD.clrScr();
        drawSettingsPage();
        page = 3;
      }
    }
  }
  if (page == 3) {
    if (touch.dataAvailable()) {
      touch.read();
      x = touch.getX();
      y = touch.getY();
      if (x >= 20 && y >= 50 && x <= 300 && y <= 100) {
        LCD.clrScr();
        drawInputScreen();
        LCD.print("Introdu ORA:", LEFT, 0);
        calcInputScreen(20);
        h = nr;
        nr = 0;
        LCD.print("Introdu MINUTELE:", LEFT, 0);
        calcInputScreen(20);
        LCD.clrScr();
        m = nr;
        nr = 0;
        page = 1;
        ok = 1;
       } else if (x >= 20 && y >= 140 && x <= 300 && y <= 190) {
        LCD.clrScr();
        drawInputScreen();
        LCD.print("Introdu ZIUA:", LEFT, 0);
        calcInputScreen(20);
        d = nr;
        nr = 0;
        LCD.print("Introdu LUNA:", LEFT, 0);
        calcInputScreen(20);
        mo = nr;
        nr = 0;
        LCD.print("Introdu ANUL:", LEFT, 0);
        calcInputScreen(20);
        yr = nr;
        nr = 0;
        LCD.clrScr();
        page = 1;
        ok = 1;
      }
    }
  }
  if (page == 2) {
    LCD.setColor(255, 255, 255);
    LCD.setFont(BigFont);
    LCD.print("INTRODU PASTILA", CENTER, 50);
    LCD.print("IN ORIFICIU", CENTER, 70);
    LCD.fillRect(7, 145, 155, 190);
    LCD.fillRect(163, 145, 311, 190);
    LCD.setColor(0, 0, 0);
    LCD.setBackColor(255, 255, 255);
    LCD.print("GATA", 206, 160);
    LCD.print("INAPOI", 34, 160);
    while(true) {    
      touch.read();
      x = touch.getX();
      y = touch.getY();
      if (x >= 7 && y >= 145 && x <= 155 && y <= 190) {
        page = 1;
        ok = 1;
        LCD.clrScr(); 
        break;
      }
      if (x >= 163 && y >= 145 && x <= 311 && y <= 190 && (tr1 == -1 || tr2 == -1 || tr3 == -1 || tr4 == -1)) {
        LCD.clrScr();
        step2();
        LCD.clrScr();
        break;
      }        
    }
  }
}
