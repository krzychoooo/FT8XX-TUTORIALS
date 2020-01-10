#include <GD23Z.h>
#include "button.h"

Button::Button(byte itemType, byte itemId, byte menuId, uint16_t posX, uint16_t posY, uint16_t width, uint16_t heigh, byte tag, byte font, const char *text){

    this->itemType = itemType;
    this->itemId = itemId;
    this->menuId = menuId;
    this->posX = posX;
    this->posY = posY;
    this->width = width;
    this->heigh = heigh;
    this->tag = tag;
    this->font = font;
    this->name = text;
    if(itemType == 0){
        this->hide = 0;
    }
    else
    {
        this->hide = 1;
    }   
}

void Button::show(){
    if(!this->hide){
        GD.Tag(this->tag);
        GD.cmd_button(this->posX, this->posY, this->width, this->heigh, this->font, 0, this->name);
    }
}

void Button::execute(void){
    if (this->buttonPushFunc != NULL)
    {
        this->buttonPushFunc();
    }
        
}

void Button::atachPushFunction(ButtonEventHandler buttonPushFunc){
    this->buttonPushFunc = buttonPushFunc;
}

Button::~Button()
{
}
