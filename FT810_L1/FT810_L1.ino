#include <SPI.h>
#include <GD3.h>
#include <stdlib.h>

#define PDpin 8

uint32_t xPosition;
# define MyButton1 233

char buffer[10];
void setup()
{
	Serial.begin(9600);
	pinMode(PDpin, OUTPUT);
	digitalWrite(PDpin, HIGH);
	delay(20);
	digitalWrite(PDpin, LOW);
	delay(20);
	digitalWrite(PDpin, HIGH);
	delay(20);
	
	GD.begin();

}

	// ka�dy piksel ma sw�j kolor RGB kana� alfa oraz TAG (0-254 + 255) 

void loop()
{
	GD.get_inputs();
	
		// czyszczenie ekranu
	GD.ClearColorRGB(0x8080ff);
	GD.Clear();
	
	itoa( GD.inputs.tag, buffer, 10);
	GD.cmd_text(400, 150, 31, OPT_CENTERX, buffer);	
		// jakim kolorem b�dziemy rysowa�
		
	GD.ColorRGB(0xff0000);				//czysty RGB 24bit
	GD.Tag(MyButton1);
		// deklarujemy co b�dziemy rysowa�
	GD.Begin(POINTS);
		//parametry obiektu do narysowania
	GD.PointSize(100*16);
		// rysujemy (wstawiamy do ramki kt�ra dopiero b�dzie wy�wietlona)
	GD.Vertex2f(400*16, 300*16);

	GD.Tag(255);
	GD.ColorRGB(0x8080ff);
	GD.PointSize(80*16);
	GD.Vertex2f(400*16, 300*16);
	
	
		
	// ko�czymy ramk� i wy�wietlamy j�
	GD.swap();
}
