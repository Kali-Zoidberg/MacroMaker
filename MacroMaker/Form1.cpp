#include "stdafx.h" 
#include "Form1.h"

using namespace CppCLR_WinformsProjekt;

bool Form1::validKey(String^ keyStr) {
	
	return false;
}

Keys Form1::getSentinelKey() {
	return sentKey;
}

int Form1::getTimer() {
	return timerTime;
}

int Form1::setTimer(int t) {

	if (t >= 0) {
		timerTime = t;
		return 0;
	} else
		return false;
}