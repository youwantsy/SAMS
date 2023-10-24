#pragma once
#include "CommunicationManager.h"

class StatusManager
{
public:
	Message message;
	Position currentPos;
	int missileNum;
	void getMessage(Message messagefromCM);
	void setInitMissileNum();
	void setPosition();

};

