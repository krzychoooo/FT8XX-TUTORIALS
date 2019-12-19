#include <Arduino.h>
#include <SPI.h>
#include <GD23Z.h>

#define Pdpin 8

#define LABEL1_TAG 200
#define LABEL1_SIZE 6
static char label1_txt[LABEL1_SIZE];

#define MESSAGE_SIZE 5
static char message[MESSAGE_SIZE];

struct keyboardStructure
{
  byte keyBoardType; //0-brak 1-numeryczna
  byte targetData;   // tag
} keyboard;

void showKeyboard(byte);

void setup()
{
  pinMode(Pdpin, OUTPUT);
  digitalWrite(Pdpin, HIGH);
  delay(20);
  digitalWrite(Pdpin, LOW);
  delay(20);
  digitalWrite(Pdpin, HIGH);
  delay(20);
  memset(message, 0x00, MESSAGE_SIZE);
  memset(label1_txt, 0x00, LABEL1_SIZE);
  GD.begin();
}

void loop()
{
  static byte key = 0, prevkey;

  GD.cmd_gradient(0, 0, 0x0000ff, 0, 599, 0x00ff00);

// LABEL 1
  GD.Tag(LABEL1_TAG);
  GD.LineWidth(4 * 16);
  GD.ColorRGB(0x00ff00);
  GD.Begin(RECTS);
  GD.Vertex2f(200 * 16, 10 * 16);
  GD.Vertex2f(600 * 16, (10 + 34) * 16);
  GD.Tag(0);
  GD.ColorRGB(0x000000);
  GD.cmd_text(400, 27, 30, 0 | OPT_CENTER, label1_txt);
//END LABEL1

// Wyświetlenie klawiatury
  showKeyboard(key);

  GD.swap();


  GD.get_inputs();
  key = GD.inputs.tag;

//reakcja na naciśnięty klawisz klawiatury
  if ((prevkey == 0x00) && (' ' <= key) && (key < 0x7f))
  {
    memmove(message, message + 1, MESSAGE_SIZE-2);
    message[MESSAGE_SIZE-2] = key;
    message[MESSAGE_SIZE-1] = 0;
  }

//wykrycie dotknięcia elementów poza klawiaturą
  if (prevkey == 0)
  {
    switch (key)
    {
    case LABEL1_TAG:        //dotknięto etykietę LABEL1
      keyboard.keyBoardType = 1;
      keyboard.targetData = LABEL1_TAG;
      memset(message, ' ', MESSAGE_SIZE-1);
      message[MESSAGE_SIZE-1] = 0;
      break;
    case 13:                //Dotknięto ENTER
      //przepisanie z okna klawiatury do celu
      memcpy(label1_txt, message, MESSAGE_SIZE);
      keyboard.keyBoardType = 0;          // wszystko zrobione i wygaszenie klawiatury
      break;

    default:
      break;
    }
  }

  prevkey = key;
}



void showKeyboard(byte key){

  switch (keyboard.keyBoardType)
  {
  case 1:
    GD.Begin(RECTS);
    GD.ColorRGB(0xffff00);
    GD.Vertex2f(30*16, 38*16);
    GD.Vertex2f(210*16, 96*16);
    GD.cmd_fgcolor(0x002070);      
    GD.cmd_keys(30, 100, 180, 60, 31, 0 | key | OPT_CENTER, "789");
    GD.cmd_keys(30, 100 + 62, 180, 60, 31, 0 | key, "456");
    GD.cmd_keys(30, 100 + 124, 180, 60, 31, 0 | key, "123");
    GD.cmd_keys(30, 100 + 186, 180, 60, 31, 0 | key, "0.");
    GD.Tag(13);
    GD.cmd_button(30, 100+186+60+2, 150, 62, 31, 0 , "ENTER");
    GD.ColorRGB(0xff0000);
    GD.cmd_text((30+210)/2, (38+96)/2, 30, 0 | OPT_CENTER, message);
    break;
  case 2:
    // TUTAJ WYŚWIETLENIE INNEJ KLAWIATURY
    break;
  default:
    break;
  }
}