#include "StatusManager.h"
#include <iostream>

void StatusManager::getMessage(Message messagefromCM)
{
	message = messagefromCM;
};

void StatusManager::setInitMissileNum() 
{
	//missileNum = 

};

void StatusManager::setPosition()
{
	currentPos.x = message.data3.x;
	currentPos.y = message.data3.y;
};
