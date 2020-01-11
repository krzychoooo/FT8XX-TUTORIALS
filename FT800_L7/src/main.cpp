#include <Arduino.h>
#include <GD23Z.h>
#include <button.h>

#define Pdpin 8
#define LedBlue A0

//          Button(byte itemType, byte itemId, byte menuuId, byte posX, byte posY, uint16_t width, uint16_t heigh, byte tag, byte font, const char* text);
Button b0(0, 0, 200, 0, 0, 160, 45, 200, 30, "setting");
Button b1 = Button(1, 1, 200, 0, 50, 160, 45, 201, 30, "set IP");
Button b2 = Button(1, 2, 200, 0, 100, 160, 45, 202, 30, "set time");

Button b3 = Button(0, 3, 203, 165, 0, 160, 45, 203, 30, "action");
Button b4 = Button(1, 4, 203, 165, 50, 160, 45, 204, 30, "reset");
Button b5(1, 5, 203, 165, 100, 160, 45, 205, 30, "set");

Button *menu[] = {
    &b0,
    &b1,
    &b2,
    &b3,
    &b4,
    &b5,
    NULL};

byte currentKeyTag, prevKeyTag;

void makeMenu(void);
void ledOn(void);
void ledOff(void);

void setup()
{
  pinMode(LedBlue, OUTPUT);
  pinMode(Pdpin, OUTPUT);
  digitalWrite(Pdpin, HIGH);
  delay(20);
  digitalWrite(Pdpin, LOW);
  delay(20);
  digitalWrite(Pdpin, HIGH);
  delay(20);
  GD.begin();
  b4.atachPushFunction(ledOff);
  b5.atachPushFunction(ledOn);
}

void loop()
{
  GD.get_inputs();

  GD.cmd_gradient(0, 0, 0x0000ff, 0, 599, 0x00ff00);
  currentKeyTag = GD.inputs.tag;
  makeMenu();
  prevKeyTag = currentKeyTag;
  GD.swap();
}

void makeMenu(){
int i;
static byte activeMenu;
static unsigned long pressTime;

  if(NULL == menu[0]){
    return;
  }

  for ( i = 0; menu[i] != NULL; i++)
  {
    if((menu[i]->menuId == currentKeyTag) && (prevKeyTag == 0)){
      activeMenu = currentKeyTag;
      pressTime = millis();
    }

    if (menu[i]->itemType == 0)
    {
      menu[i]->hide = 0;
    }
    else
    {
      if (menu[i]->menuId == activeMenu)
      {
        menu[i]->hide = 0;
      }
      else
      {
        menu[i]->hide = 1;
      }
    }

    menu[i]->show();    

    if ((menu[i]->tag == currentKeyTag) && (prevKeyTag == 0))
    {
      menu[i]->execute();
      pressTime = millis();
    }
    
  }
  
  if (pressTime + 4000 < millis())
  {
    activeMenu = 0;
  }
}


void ledOn(){
  digitalWrite(LedBlue, LOW);
}
void ledOff(){
  digitalWrite(LedBlue, HIGH);
}

