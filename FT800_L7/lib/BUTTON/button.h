#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>

typedef void (*ButtonEventHandler)();

class Button
{
private:
    ButtonEventHandler buttonPushFunc = NULL;
public:
    byte itemType;  //0-menu 1 - submenu
    byte itemId;
    byte menuId;
    byte font;
    byte tag;
    byte hide;
    uint16_t posX, posY, width, heigh;
    const char *name;
    
    
    Button(byte itemType, byte itemId, byte menuId, uint16_t posX, uint16_t posY, uint16_t width, uint16_t heigh, byte tag, byte font, const char* text);
    void show(void);
    void atachPushFunction(ButtonEventHandler buttonPushFunc);
    void execute(void);
    ~Button();

};

#endif