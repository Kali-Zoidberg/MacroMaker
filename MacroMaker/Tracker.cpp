/*
TODO: 
comment functions
$$ For shift, if shift then a letter, upper case but only once.
$$ The rest should be converted to  lower case.
$$ Conversions. check for lshift x
$$ Deal with numbers. 
Make the convert file to string more implementable. have another function that adds the  "{" and "}". oh wait we can just use the format function.
Convert the other oem keys and have cases for them.
*/

#include "stdafx.h"
#include "Tracker.h"

Tracker::Tracker() {
	nameOfFile = "default.txt";
}

Tracker::Tracker(String^ nameOfFile) {

	Tracker::nameOfFile = nameOfFile;

}
void Tracker::beginTracking() {
	
}

void Tracker::flushVector() {
	int vect_Length = keyInputs.size();
	for (int i = 0; i < vect_Length; ++i) 
		keyInputs.pop_back();
}

void Tracker::makeLower(String^% keystr) {
	if (keystr->Length <= 3) //this guarantees it is a single character so we can make it a lower case. Sicne everything else is > that one character.
		keystr = keystr->ToLower();

}
bool Tracker::parseOem(String^% keystr) {
	String^ tempsubstr = "{";
	int keystr_length = keystr->Length;

		switch (keystr[4]) {

		case '1':
			keystr = ";";
			break;
		case '2':
			keystr = "\?";
			break;
		case '3':
			keystr = "~";
			break;
		case '4':
			keystr = "[";
			break;
		case '5':
			keystr = "\\";
			break;
		case '6':
			keystr = "]";
			break;
		case '7':
			keystr = "'";
			break;
			return false;
		case '8':
			keystr = ":";
			break;
		default:
			tempsubstr += keystr->Substring(4, keystr_length - 4); // "{" + substring
			keystr = tempsubstr;
			break;
		}
	
	return true;
}

bool Tracker::convertFileToString(String^ fn) {

	String^ readStr = " ";
	String^ tempDoub = " ";
	String^ tempKeyStr = " ";
	Text::UTF8Encoding utf8(true);

	bool isWritingNum = false;
	bool isWritingKey = false;
	__int64 fileLength = 0;


	if (!keyInputs.empty()) {
		flushVector();
	}
	try {
		presetFile = gcnew FileStream(fn, FileMode::Open, FileAccess::Read); //throw an exception so program doesn't crash? no wait we still need tor eject invalid file names...
	}
	catch (const ArgumentException^ e) {
		Debug::WriteLine("Error reading file. Invalid File name \n");
		return false;
	}
	catch (const IOException^ e) {
		Debug::WriteLine("File already open. \n");
	}

	fileLength = presetFile->Length;

	array<Byte> ^ curByte = gcnew array<Byte>(fileLength);
	
	presetFile->Read(curByte, 0, fileLength);
	readStr = utf8.GetString(curByte,0,fileLength);


	//Diagnostics::Debug::WriteLine("file Length: " + fileLength + " curByte Length: " + curByte->Length + " \n");
	//Diagnostics::Debug::WriteLine(readStr);

	__int64 index = 0; //current index to keep track of which vector element we are at.
	
	for (__int64 i = 0; i < fileLength; ++i) {
		keyStructure^ tempKeyStruct = gcnew keyStructure; //does this lead to a memory leak? maybe not becaues the vector now points to this and will be deleted when the vector is deconstructed??

		//MAYBE MAKE SUBSTRING SO IT SEARCHES AND KEEPS TRACK OF LAST | this si too hacky down there
		//sub string or byte to byte?
		//sub strings...
		
		if (isWritingKey && readStr[i] != '\\') {
			tempKeyStr += readStr[i];
		}

		if (readStr[i] == '|') {
			
			tempKeyStr = "";
			//tempKeyStr += "{";
			isWritingNum = false;
			isWritingKey = true;

			try {

				//Diagnostics::Debug::WriteLine("ize of truct" + keyInputs.size() + " i: " + i + " index: " + index);
				tempKeyStruct->keyStrokeTimes = Convert::ToDouble(tempDoub);
		
				keyInputs.push_back(tempKeyStruct);
			}
			catch (const FormatException^ e) {
			}
		}

		if (isWritingNum) {
			tempDoub += readStr[i];
		}

		if (readStr[i] == '\\' || readStr[i] == '*') {
			if (readStr[i] == '\\' && i > 0)
			//	tempKeyStr += "}";
			tempDoub = "";
			isWritingKey = false;
			isWritingNum = true;

			if (i > 0) {
				makeLower(tempKeyStr);
				keyInputs.at(index)->keyStrokes = tempKeyStr;
				++index;
			}
		}
	}
	return true;
}


int Tracker::writeKey(double tstart, double tdiff, String^ keyStr) {
	//macrotime up for uhm shift. no wait do only one shift at a time.
	macroTimes.push_back(tdiff);
	macroKeys.push_back(keyStr);
	return 0;

}


int Tracker::writeTimeUp(double tup, Keys k) {
	//double tdiff = 
	//macroTimeUp.push_back(t);
	//macroKeyUp.push_back(k);
	return 0;
}


bool Tracker::setFileName(String^ fn) {
	if (isValidFN(fn)) {
		nameOfFile = fn;
		Diagnostics::Debug::WriteLine(fn);
		return true;
	}
	else
		return false;
}


String^ Tracker::getFileName() {
	return nameOfFile;
}


bool Tracker::isValidFN(String^ fn) {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < fn->Length; ++j) {
			if (fn[j] == invalidChars[i]) { // searches whole string for chars.
				std::cout << "Invalid file name. \n";
				return false;
			}
		}
	}
	return true;
}


int Tracker::createFile() {
	//ostringstream osstr;
	String^ tempStr = "*";
	if (!isValidFN(nameOfFile))
		return -1; //redundant??

	try {
		
		trackingFile = gcnew FileStream(nameOfFile, FileMode::OpenOrCreate, FileAccess::ReadWrite);
		
	}
	catch (const ArgumentException ^e) {
		std::cout << "Invalid file name. \n";
		return -2;
	}


	for (int i = 0; i < macroTimes.size(); ++i) {

		//Debug::WriteLine(macroTimes.at(i));
		tempStr += macroTimes.at(i) + "|";
		tempStr += macroKeys.at(i) + "\\";

	}

	array<Byte>^tempStrToByte = (gcnew System::Text::UTF8Encoding(true))->GetBytes(tempStr);

	trackingFile->Write(tempStrToByte, 0, tempStrToByte->Length);
	trackingFile->Close();
	
	convertFileToString(nameOfFile);
	return 0;

}


bool Tracker::convertKeyStrings(String^% keystr) {

	String^ tempsubstr = "{";
	int keystr_length = keystr->Length;

	if (keystr_length > 4 && keystr->Substring(0, 4)->Equals("{Oem"))
		parseOem(keystr);
	if (keystr_length == 4) //the {D#} keys
	{
		tempsubstr += keystr->Substring(2, 2);
		keystr = tempsubstr;
	}
	if (keystr->Equals("{Period}"))
		keystr = "{.}";
	if (keystr->Equals("{Return}"))
		keystr = "{~}"; //converts return to enter.
	if (keystr->Equals("{Space}")) //converts space
		keystr = " ";
	if (keystr->Equals("{Pause}"))
		keystr = "{Break}";
	if (keystr->Equals("{Escape}"))
		keystr = "{ESC}";
	if (keystr->Equals("{Back}"))
		keystr = "{BS}";
	if (keystr->Equals("LControlKey")) {
		keystr = "^";
		return true;
	}
	if (keystr->Equals("{ShiftKey}")) {
		keystr = "+";
		return true;
	}
	if (keystr->Equals("{RControlKey}")) {
		keystr = "^";
		return true;
	}
	if (keystr->Equals("{LShift}")) {
		keystr = "+";
		return true;
	}
	if (keystr->Equals("{RShift}")) {
		keystr = "+";
		return true;
	}
	if (keystr->Equals("{LAlt}"))
		keystr = "{%}";
	if (keystr->Equals("{RAlt}"))
		keystr = "{%}";
	if (keystr->Equals("{PrintScreen}"))
		keystr = "{PRTSC}";
	if (keystr->Equals("{Scroll}"))
		keystr = "{SCROLLLOCK}";
	if (keystr->Equals("{Next}") || keystr->Equals("{PageDown}"))
		keystr = "{PGDN}";
	if (keystr->Equals("{Prior}") || keystr->Equals("{PageUp}"))
		keystr = "{PGUP}";
	
	return false;
}


bool Tracker::proccessKeyStroke(String^% keystr) {
	
	if (convertKeyStrings(keystr)) {
		return true;
	}
	else {
		try {
			SendKeys::Send(keystr);
		} catch (const System::ArgumentException^ e) {

			Debug::WriteLine("Error, key could not be processed for it is not supported. Key: " + keystr);
		
		}
	}
	return false;
}


bool Tracker::runMacro(String^ fn) {

	Stopwatch^ s_watch = gcnew Stopwatch();

	__int64 timeDiff = 0;
	__int64 curTime = 0;
	int keyVectorSize = 0;
	s_watch->Start();
	curTime = s_watch->ElapsedMilliseconds;
	DateTime^ dt = DateTime::Now;
	Debug::WriteLine(dt->Millisecond);

	do {

		timeDiff = s_watch->ElapsedMilliseconds - curTime;

	} while (timeDiff <= 500);  //make this the delay constant

	s_watch->Stop();

	if (convertFileToString(fn)) {

		keyVectorSize = keyInputs.size();
		
		for (__int64 i = 0; i < keyVectorSize; ++i) {

			s_watch->Start();
			curTime = s_watch->ElapsedMilliseconds;

			do {
				timeDiff = s_watch->ElapsedMilliseconds - curTime;
			} while (timeDiff <= keyInputs.at(i)->keyStrokeTimes);
			
			if (proccessKeyStroke(keyInputs.at(i)->keyStrokes)) {
				
				if (i < keyVectorSize - 1 && keyInputs.at(i + 1)->keyStrokes->Length <= 3) { //right now we just check to see if it is a ingle char. May need to alter once 
					
					String^ tempKeyStroke = keyInputs.at(i)->keyStrokes + keyInputs.at(i + 1)->keyStrokes[1]; //the special character + char between the {}
					keyInputs.at(i + 1)->keyStrokes = tempKeyStroke;
				
				} else 
					proccessKeyStroke(keyInputs.at(i)->keyStrokes);
		
			}

		//	Diagnostics::Debug::WriteLine("KeyStrokes size: " + keyInputs.size() );
		//
			//Diagnostics::Debug::WriteLine("Current stream: " + keyInputs.at(i)->keyStrokes + "Current delay: " + keyInputs.at(i)->keyStrokeTimes + "current index: " + i);
			s_watch->Stop();
			
	}

	} else
		return false; // file not found or is not valid. Return false.
	return true;

	
}