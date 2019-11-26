#include <Arduino.h>
#include <SPI.h>
#include <GD23Z.h>
#include <MemoryFree.h>

#define TAG_BUTTON_HOME 200
#define TAG_BUTTON_WATCH 201

enum screen_page
{
	HOME_PAGE,
	WATCH_PAGE
};

#define Pdpin 8

byte make_page(int);

void setup()
{
	pinMode(Pdpin, OUTPUT);
	digitalWrite(Pdpin, HIGH);
	delay(20);
	digitalWrite(Pdpin, LOW);
	delay(20);
	digitalWrite(Pdpin, HIGH);
	delay(20);

	GD.begin();
	Serial.begin(9600);
}

void loop()
{
	static screen_page page = WATCH_PAGE;
	static byte key = 255;

	key = make_page(page);

	switch (key)
	{
	case TAG_BUTTON_HOME:
		page = HOME_PAGE;
		break;
	case TAG_BUTTON_WATCH:
		page = WATCH_PAGE;
		break;

	default:
		break;
	}

	/**************************** my application **********************************/
}

byte make_page(int page)
{

	switch (page)
	{
	case HOME_PAGE:
		GD.get_inputs();

		GD.cmd_gradient(0, 0, 0x0000ff, 0, 599, 0x00ff00);

		GD.Tag(TAG_BUTTON_WATCH);
		GD.cmd_button(600, 16, 150, 34, 24, 0, "ZEGAR");

		GD.swap();
		break;

	case WATCH_PAGE:
		GD.cmd_gradient(0, 0, 0x00ff00, 0, 599, 0x0000ff);

		GD.Tag(TAG_BUTTON_HOME);
		GD.cmd_button(450, 16, 150, 34, 24, 0, "HOME");

		GD.cmd_number(400, 150, 30, 0, freeMemory());

		GD.swap();
		break;

	default:
		break;
	}

	GD.get_inputs();

	return GD.inputs.tag;
}
