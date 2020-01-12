#include <Arduino.h>
#include <GD23Z.h>

#define pdPin 8

int Centro = 240 / 2; //CMP1.png, 240x240 px, Centro=240/2,   compass
int Centro2 = 252 / 2; //Pn1.png, 252x252 px, Centro=240/2,   indicator

float angleValue1, direction1 = -1.0;
float angleValue2, direction2 = 1.0;

void compass1(void);
static void rotate_Center(float a, int CX, int CY);

void setup()
{
  pinMode(pdPin, OUTPUT);
  digitalWrite(pdPin, HIGH);
  delay(20);
  digitalWrite(pdPin, LOW);
  delay(20);
  digitalWrite(pdPin, HIGH);
  delay(20);

  GD.begin();

  //open("CMP1.png");  //compass 240x240
  GD.BitmapHandle(0);
  GD.cmd_loadimage(0, 0);
  GD.load("CMP1.png");

  //open("Bru1.png");  // compass 250x251 precize
  GD.BitmapHandle(1);
  GD.cmd_loadimage(-1, 0);
  GD.load("Bru1.png");

  //open("Pn1.png");  //wskazówka 252x252
  GD.BitmapHandle(2);
  GD.cmd_loadimage(-1, 0);
  GD.load("Pn1.png");

  //open("DX12.jpg");  // tło
  GD.BitmapHandle(3);
  GD.cmd_loadimage(-1, OPT_MONO);
  GD.load("DX12.jpg");

  //open("switch.png");  // switch  164x131
  GD.BitmapHandle(4);
  GD.cmd_loadimage(-1, 1);
  GD.load("switch.png");

  
}

void loop()
{
  compass1();
}

void compass1()
{
  static byte key, prevkey;
  static bool stateKey;

  GD.get_inputs();
  key = GD.inputs.tag;
  if (prevkey == 0 && key == 201)
  {
    stateKey = !stateKey;
  }
  

  prevkey = key;

  GD.ClearColorRGB(0xffff00);
  GD.Clear();

  //GD.Begin(BITMAPS);
  //GD.Vertex2ii(0, 0, 3);
  
  GD.SaveContext();
  GD.Begin(BITMAPS);
  angleValue1 = angleValue1 + direction1; //GD.printNfloat(500, 20, angleValue1, 1, 31);
  if (angleValue1 <= -360*20)
  {
    direction1 = 1.0;
  }
  if (angleValue1 >= 0)
  {
    direction1 = -1.0;
  }
  
  rotate_Center(DEGREES(angleValue1), Centro, Centro);
  GD.cmd_setmatrix();
  GD.ColorA(128);
  GD.Vertex2ii(300, 100, 0);
  GD.cmd_loadidentity();
  GD.End();
  GD.RestoreContext();


  GD.SaveContext();
  GD.Begin(BITMAPS);
  GD.Vertex2ii(150, 100, 1);
  GD.End();
  GD.RestoreContext();

  GD.SaveContext();
  GD.Begin(BITMAPS);
  rotate_Center(DEGREES(angleValue1), 125, 129);
  GD.cmd_setmatrix();
  GD.Vertex2ii(149,100, 2);
  GD.cmd_loadidentity();
  GD.End();
  GD.RestoreContext(); 

  GD.SaveContext();
  GD.Tag(201);
  GD.Begin(BITMAPS);
  GD.ScissorSize(75, 131);
  GD.ScissorXY(450,10);
  if (stateKey)
  {
    GD.Vertex2ii(450, 10, 4);
  }
  else
  {
    GD.Vertex2ii(450-164+75, 10, 4);
  }
  
  
  
  GD.End();
  GD.RestoreContext(); 

  GD.swap();
}

static void rotate_Center(float a, int CX, int CY)
{
  GD.cmd_translate(F16(CX), F16(CY));
  GD.cmd_rotate(a);
  GD.cmd_translate(F16(-CX), F16(-CY));
}


