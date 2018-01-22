#pragma once

#include <fstream>
#include <iostream>
#include <cliext/vector>
#include <iomanip>

using namespace System::Windows::Forms;
using namespace System::Diagnostics;
using namespace System::IO;
using namespace System;

public ref struct keyStructure {

	double macroTimeUp;
	double macroTimeStart;
	double keyStrokeTimes;
	String^ keyStrokes;
	Keys macroKeyUp;

};


public ref class Tracker {

	/*
	write keys to a string
	write string to file so we dont re open and close each time.
	maybe do a linked list so one key stroke points to the next and when that time is up it points to the next one? How would we read from text file. Easy make a function that reads a file and creates nodes based on it.
	Too many || vectors. Create a class.
	*/

public:

	Tracker();
	Tracker(String^ nameOfFile);


	///<summary>
	///Tracks all keyboard input using win32 api.
	///</summary>
	///<param name = "beg_key"> The initiating key. </param>
	///</param name = "sent_key"> The sentinel key. </param>

	void beginTracking();


	///<summary>
	///Writes KeyCodes to a text file.
	///Text file format: TimeDown|Key\TimeDownNext|KeyNext
	///					 TimeUp\NextTimeUp
	///</summary>
	///<param name = "t">The time between the last key and current key. </param>
	///<param name = "k">The KeyCode to pass to the text file. </param>
	///<return> Returns 0 if succesful, -1 otherwise.

	int writeKey(double tstart, double tdiff, String^ keyStr);

	//bool writeLocation(int x, int y);

	///<summary>
	///Writes KeyCodes to a text file.
	///Text file format: TimeDown|Key|TimeDownNext|KeyNext
	///					 TimeUp\NextTimeUp
	///</summary>
	///<param name = "t">The time between the last key and current key. </param>
	///<param name = "k">The KeyCode to pass to the text file. </param>
	///<return> Returns 0 if succesful, -1 otherwise.

	int writeTimeUp(double tup, Keys k);


	///<summary>
	///Creates a file to write the sequences of inputs.
	///</summary>
	///<param name = "nameOfFile"> Writes the name of the files. </param>
	///<return> Returns 0 if the operation is succesful. Returns -1 if another file with the same name exists. Returns -2 if the file name is invalid.
	///

	int createFile();


	///<summary>
	///Reads the specified file and converts it to a string.
	///</summary>
	///<param name = "fn"> The file name to convert to a string. </param>
	///<return> Returns true if the file exists. Otherwise, it returns false. </return>

	virtual bool convertFileToString(String^ fn);

	///<summary>
	///Retrieves the file name.
	///</summary>
	///<return> Returns the file name as a string. </return>

	virtual String^ getFileName();


	///<summary>
	///Sets the file name.
	///</summary>

	virtual bool setFileName(String^ fn);
	///<summary>
	///Processes Key strokes with format {String
	///</summary>
	///<param name = "keystr"> The key stroke to process </param>
	///
	bool proccessKeyStroke(String^% keystr);

	///<summary>
	///Control logic for running
	///</summary>
	///<param name = "fn"> The file name that contains the preset macro to run. </param>
	///<return> Returns true if the file is found, otherwise it returns false. </return>

	bool runMacro(String^ fn);
	///<summary>
	///Makes all numerical and alphabetical characters lower case so that things like shift work properly.
	///</summary>
	///<param name = "keystr"> The keycode string to process </param>
	
	void makeLower(String^% keystr);

	///<summary>
	///Parses Oem keys
	/// </summary>
	///<param name = "keystr"> the keycode string to process. Passed by reference and is modified. </param>
	///<return> Returns true if succesful, false otherwise. </param>
	bool parseOem(String^% keystr);


private:

	cliext::vector<keyStructure^> keyInputs;
	bool convertKeyStrings(String^% keystr);
	String ^ nameOfFile;
	cliext::vector<double> macroTimeUp;
	cliext::vector<double> macroTimes; //too many parallel vectors. Create class
	cliext::vector<double> macroTimeStart;
	cliext::vector<double> keyStrokeTimes;
	cliext::vector<String^> keyStrokes;
	cliext::vector<String^> macroKeys;
	cliext::vector<Keys> macroKeyUp;

	static array<char> ^invalidChars = gcnew array<char> {'<', '>', ':', '\"', '/', '\\', '|', '?', '*'};
	FileStream ^presetFile;
	FileStream ^trackingFile;

	///<summary>
	///Checks to see if the desired string name is invalid. Of course this should be checked when they input it in the preset??
	///</summary>
	///<param name = "fn"> File name string </param>
	///<return> Returns true if the file name is valid. </return>

	bool isValidFN(String^ fn);

	void flushVector(); //flushes vector. basically clears preset

};
