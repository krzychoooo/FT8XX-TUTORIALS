//#include <Tp1.h>
//#include <Rad1.h>
#include <GD23Z.h>
#include <SPI.h>

#define pdPin 8
#define CARTAG 129

void setup()
{
Serial.begin(9600);
pinMode(pdPin, OUTPUT);
digitalWrite(pdPin, HIGH);
delay(20);
digitalWrite(pdPin, LOW);
delay(20);
digitalWrite(pdPin, HIGH);
delay(20);

GD.begin();

GD.BitmapHandle(0);
GD.cmd_loadimage(0, 0);
GD.load("DX12.jpg");

GD.BitmapHandle(1);
GD.cmd_loadimage(-1, 0);
GD.load("car.png");
}


void loop()
{
	static int16_t xTouch, xDelta, xCar;
	static int16_t yTouch, yDelta, yCar;
	static int16_t shadowOffset, pictureOffset;
	static byte oldTag;
	
	GD.get_inputs();
	
	
	shadowOffset = 0;
	pictureOffset = 0;
	if (GD.inputs.tag == CARTAG)
	{
		shadowOffset = 15;
		pictureOffset = 5;
		if (oldTag == 0)
		{
			xDelta = GD.inputs.tag_x - xCar;
			yDelta = GD.inputs.tag_y - yCar;
		}
		xCar = GD.inputs.tag_x - xDelta;
		yCar = GD.inputs.tag_y - yDelta;
		
		if (xCar<0) xCar = 0;
		if (yCar<0) yCar = 0;
		if (xCar > 800-198) xCar = 800-198;
		if (yCar > 480-83) yCar = 480-83;
		
		
	}
	oldTag = GD.inputs.tag;
	
	Serial.println(xCar);
	
	GD.Clear();
	
	GD.Begin(BITMAPS);
	GD.Tag(255);
	GD.Vertex2ii(0, 0, 0);
	
	GD.ColorRGB(0x000000);
	GD.ColorA(80);				//transparentnoœæ 0-255
	GD.Begin(RECTS);
	GD.LineWidth(10*16);	//promieñ naro¿nika
	GD.Vertex2f((xCar+shadowOffset+10)*16, (yCar+shadowOffset+10)*16);
	GD.Vertex2f((xCar + 197+shadowOffset-10)*16, (yCar + 83+shadowOffset-10)*16);
	
	GD.ColorA(255);
	GD.ColorRGB(0xFFFFFF);
	GD.Tag(CARTAG);
	GD.Begin(BITMAPS);
	GD.BitmapHandle(1);
	GD.Vertex2f((xCar-pictureOffset)*16, (yCar-pictureOffset)*16);
	
	GD.swap();
}