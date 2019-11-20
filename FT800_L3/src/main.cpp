#include <Arduino.h>
#include <SPI.h>
#include <GD23Z.h>
#include <Servo.h>

#define Pdpin 8
#define TAG_DIAL 200
#define TAG_SLIDER 201
#define TAG_TOGLE 202
#define TAG_BUTTON_OK 203

#define BLUE_LED A0

Servo MG996R;

void setup()
{
	MG996R.attach(A1);
	pinMode(BLUE_LED, OUTPUT);
	pinMode(Pdpin, OUTPUT);
	digitalWrite(Pdpin, HIGH);
	delay(20);
	digitalWrite(Pdpin, LOW);
	delay(20);
	digitalWrite(Pdpin, HIGH);
	delay(20);

	GD.begin();
}

void loop()
{
	static uint16_t dial_value = 0, slider_value, togle_value, option_button_ok;

	GD.get_inputs();

	switch (GD.inputs.track_tag & 0xFF)
	{
	case TAG_DIAL:
		dial_value = GD.inputs.track_val;
		break;
	case TAG_SLIDER:
		slider_value = GD.inputs.track_val;
		break;
	case TAG_TOGLE:
		if (GD.inputs.track_val > 65535/2)
		{
			togle_value = 65535;
			digitalWrite(BLUE_LED, HIGH);
		}
		else
		{
			togle_value = 0;
			digitalWrite(BLUE_LED, LOW);
		}
		break;
	case TAG_BUTTON_OK:
		option_button_ok = OPT_FLAT;
		break;
	default:
		option_button_ok = 0;
		break;
	}


	MG996R.write(map(dial_value, 0, 65535, 0, 180));

	GD.cmd_gradient(0, 0, 0x0000ff, 0, 599, 0x00ff00);

	GD.Tag(TAG_DIAL);
	GD.cmd_dial(700, 350, 90, 0, dial_value);
	GD.cmd_track(700, 350, 1, 1, TAG_DIAL);
	GD.cmd_number(700, 350, 27, 0, dial_value);
	
	GD.cmd_bgcolor(0xb9b900);
	GD.Tag(TAG_SLIDER);
	GD.cmd_slider(16, 16, 200, 20, 0, slider_value, 65535);		//opt == 0 => default 3D
	GD.cmd_track(16, 16, 200, 20, TAG_SLIDER);

	GD.Tag(TAG_TOGLE);
	GD.cmd_toggle(300, 16, 100, 30, 0, togle_value, "OFF\xFFON");		//wysokość = font(h) * 20/16 pixel
	GD.cmd_track(300, 16, 100, (uint16_t)(30*20/16), TAG_TOGLE);

	GD.cmd_gauge(150, 200, 140, 0 | OPT_NOBACK, 10, 10, dial_value, 65535 );
	
	GD.cmd_clock(400, 300, 120, 0
								| OPT_NOSECS 			// bez sekundnika
								//| OPT_NOTICKS 			//bez znaczników
								| OPT_NOBACK 			// bezcyferblatu
								//| OPT_NOHANDS			// bez wskazówek
								, 15, 45, dial_value, 0);

	GD.Tag(TAG_BUTTON_OK);
	GD.cmd_button(650, 20, 100, 50, 28, option_button_ok, "OK");								

	GD.swap();
}
