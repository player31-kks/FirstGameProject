#pragma once
#include <string>

std::string GetResourceDir() 
{
#ifdef NDEBUG // release build
	return "assets/";
#else
	return "C:/Users/USER/source/repos/player31-kks/FirstGameProject/LightYearsGame/assets/";
#endif
}
