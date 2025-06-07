#include "framework/Object.h"
#include "framework/Core.h"

ly::Object::Object()
	:mIsPendingObject{false}
{
}

ly::Object::~Object()
{
	LOG("Obejct Destory");
}

void ly::Object::Destory()
{
	mIsPendingObject = true;
}
