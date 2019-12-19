#include <Arduino.h>
#include <SPI.h>
#include <GD23Z.h>

#define Pdpin 8
#define BUTTON_READ_TAG 200
#define NBLOBS 128
#define OFFSCREEN -16384

/* struct my_xy
{
	int x, y;
} blobs[NBLOBS];
void make_blobs(void);
*/

enum {
	IDLE, READ_SENSOR
} stateMachine;

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
/* 	for (int i = 0; i < NBLOBS; i++)
	{
		blobs[i].x = OFFSCREEN;
		blobs[i].y = OFFSCREEN;
	} */
}

void loop()
{
	static byte key, prevKey;
	static unsigned long t1, t2;
	static uint16_t positions;
	static uint16_t progres;

	//TOUCH
	t1 = millis();
	GD.get_inputs();
	key = GD.inputs.tag;
	if (prevKey == 0 && key == BUTTON_READ_TAG) {
		stateMachine = READ_SENSOR;
		progres = 512;
	}
	t2 = millis();
	prevKey = key;

	// DISPLAY
	GD.cmd_gradient(0, 0, 0x0000ff, 0, 599, 0x00ff00);

	GD.Tag(BUTTON_READ_TAG);
	GD.cmd_button(600, 10, 200, 60, 30, 0, "READ");
	//make_blobs();
	if (stateMachine == READ_SENSOR)
	{	
		GD.Begin(POINTS);
		GD.PointSize(20*16);
		GD.Vertex2f(400*16, (positions)*16);
		positions += 20;
		GD.cmd_progress(100, 400, 400, 20, 0, 512 - progres, 512);		// 
		GD.cmd_spinner(400, 240, 2, 2);			//style; 0 is circular, 1 is linear, 2 is a clock,    scale: 0 - 2
	}
	GD.cmd_number(650, 200, 30, 0, t2 - t1);
	GD.swap();

	//APLICATION
	switch (stateMachine)
	{
	case READ_SENSOR:
		delay(50);
		if(--progres == 0)
			stateMachine = IDLE;
		break;
	default:
		break;
	}
}

/* void make_blobs()
{
	static byte blob_i;

	if (GD.inputs.x != -32768)
	{
		blobs[blob_i].x = GD.inputs.x << 4;
		blobs[blob_i].y = GD.inputs.y << 4;
	}
	else
	{
		blobs[blob_i].x = OFFSCREEN;
		blobs[blob_i].y = OFFSCREEN;
	}
	blob_i = (blob_i + 1) & (NBLOBS - 1);
	//GD.ClearColorRGB(0xe0e0e0);
	//GD.Clear();
	GD.Begin(POINTS);
	for (int i = 0; i < NBLOBS; i++)
	{
		// Blobs fade away and swell as they age
		GD.ColorA(i << 1);
		GD.PointSize((1024 + 16) - (i << 3));
		// Random color for each blob, keyed from (blob_i + i)
		uint8_t j = (blob_i + i) & (NBLOBS - 1);
		byte r = j * 17;
		byte g = j * 23;
		byte b = j * 147;
		GD.ColorRGB(r, g, b);
		// Draw it!
		GD.Vertex2f(blobs[j].x, blobs[j].y);
	}
} */












