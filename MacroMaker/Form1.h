#pragma once
#include <iostream>
#include "Tracker.h"
#include <time.h>



/*
TODO: Add preset name field and load from drop bar
Figure out what to do when file name is not correct.
Support how long key is down and when it goes up. This will require more effort and thought.
set name might be deprecated because it sets the default text to null. 

Moue input: when mouse down or up, get location.
write pecial characters denoting moue input. Format could be ^Button[x,y\
1. Add string format for keycodes and moue inputs. Tracker::macroKeys becoems a string^. remove the addiontal { and }
2. Presets->Load sentinel and begin keys
3. Check for .txt
*/

namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void) {

			InitializeComponent();
			isTracking = false;
		
			this->KeyPreview = true;
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyUp);

			sentKeyStr = "P";
			timerstr = "0";
			timerTime = 0;
			curTime = clock();
			lastTime = clock();
			kd_timeDiff = 0.0;
			ku_timeDiff = 0.0;
			sentKey = Keys::Escape;
			begKey = Keys::Home;
			curBegKey = Keys::None;
			curSentKey = Keys::None;
			curKeyDown = Keys::None;

		}
	
		Keys getSentinelKey();

		int getTimer();
		///<summary>
		///This sets the timer with specified amount of time in seconds.
		///</summary>
		///<param name="t">Specified time in seconds </param>
		///<returns>Returns 0 if the time t is a valid number. Otherwise it returns -1. </returns>
		int setTimer(int t);


	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  sentinelLabel;
	protected:

	private: System::Windows::Forms::TextBox^  sentinelBox;
	private: System::Windows::Forms::Button^  sentinelBut;


	private: System::Windows::Forms::TextBox^  timerBox;
	private: System::Windows::Forms::Label^  timerLabel;


	private: System::Windows::Forms::Button^  timerBut;


	protected:

	protected:

	private:

		String ^ sentKeyStr;
		String ^ timerstr;
		Keys sentKey;
		Keys begKey;
		Keys curSentKey;
		Keys curBegKey;
		Keys curKeyDown;
		Keys curKeyUp;
		Tracker track;
		time_t curTime;
		time_t lastTime;

		int timerTime;
		double kd_timeDiff; // How between seperate key presses
		double ku_timeDiff; //How long the key was up.
		bool isTracking;

		private: System::Windows::Forms::Label^  user_sent_lab;
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  beginKeyLabel;
		private: System::Windows::Forms::TextBox^  beginKeyText;
		private: System::Windows::Forms::Button^  beginBut;
		private: System::Windows::Forms::Label^  fnLabel;
		private: System::Windows::Forms::TextBox^  fnBox;
		private: System::Windows::Forms::Button^  fnBut;
		private: System::Windows::Forms::Button^  runBut;
	private: System::Windows::Forms::Label^  presetLabel;
	private: System::Windows::Forms::TextBox^  presetBox;
	private: System::Windows::Forms::Button^  presetBut;
	private: System::Windows::Forms::Label^  userBeginLabel;
	

		///<summary>
		///Determines if a key is valid
		///</summary>
		///<param name="keystr">The string inputed in the sentinel box </param>
		bool validKey(String^ keystr);

		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->sentinelLabel = (gcnew System::Windows::Forms::Label());
			this->sentinelBox = (gcnew System::Windows::Forms::TextBox());
			this->sentinelBut = (gcnew System::Windows::Forms::Button());
			this->timerBox = (gcnew System::Windows::Forms::TextBox());
			this->timerLabel = (gcnew System::Windows::Forms::Label());
			this->timerBut = (gcnew System::Windows::Forms::Button());
			this->user_sent_lab = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->beginKeyLabel = (gcnew System::Windows::Forms::Label());
			this->beginKeyText = (gcnew System::Windows::Forms::TextBox());
			this->beginBut = (gcnew System::Windows::Forms::Button());
			this->userBeginLabel = (gcnew System::Windows::Forms::Label());
			this->fnLabel = (gcnew System::Windows::Forms::Label());
			this->fnBox = (gcnew System::Windows::Forms::TextBox());
			this->fnBut = (gcnew System::Windows::Forms::Button());
			this->runBut = (gcnew System::Windows::Forms::Button());
			this->presetLabel = (gcnew System::Windows::Forms::Label());
			this->presetBox = (gcnew System::Windows::Forms::TextBox());
			this->presetBut = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// sentinelLabel
			// 
			this->sentinelLabel->AutoSize = true;
			this->sentinelLabel->Location = System::Drawing::Point(3, 13);
			this->sentinelLabel->Name = L"sentinelLabel";
			this->sentinelLabel->Size = System::Drawing::Size(66, 13);
			this->sentinelLabel->TabIndex = 0;
			this->sentinelLabel->Text = L"Sentinel Key";
			this->sentinelLabel->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// sentinelBox
			// 
			this->sentinelBox->Location = System::Drawing::Point(85, 13);
			this->sentinelBox->MaxLength = 20;
			this->sentinelBox->Name = L"sentinelBox";
			this->sentinelBox->Size = System::Drawing::Size(100, 20);
			this->sentinelBox->TabIndex = 1;
			this->sentinelBox->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged_1);
			this->sentinelBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::textBox1_KeyDown);
			// 
			// sentinelBut
			// 
			this->sentinelBut->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->sentinelBut->Location = System::Drawing::Point(193, 9);
			this->sentinelBut->Name = L"sentinelBut";
			this->sentinelBut->Size = System::Drawing::Size(52, 24);
			this->sentinelBut->TabIndex = 2;
			this->sentinelBut->Text = L"Confirm";
			this->sentinelBut->UseVisualStyleBackColor = true;
			this->sentinelBut->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// timerBox
			// 
			this->timerBox->Location = System::Drawing::Point(85, 103);
			this->timerBox->Name = L"timerBox";
			this->timerBox->Size = System::Drawing::Size(100, 20);
			this->timerBox->TabIndex = 3;
			// 
			// timerLabel
			// 
			this->timerLabel->AutoSize = true;
			this->timerLabel->Location = System::Drawing::Point(11, 103);
			this->timerLabel->Name = L"timerLabel";
			this->timerLabel->Size = System::Drawing::Size(56, 13);
			this->timerLabel->TabIndex = 4;
			this->timerLabel->Text = L"Max Time:";
			this->timerLabel->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// timerBut
			// 
			this->timerBut->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->timerBut->Location = System::Drawing::Point(193, 103);
			this->timerBut->Name = L"timerBut";
			this->timerBut->Size = System::Drawing::Size(52, 24);
			this->timerBut->TabIndex = 5;
			this->timerBut->Text = L"Confirm";
			this->timerBut->UseVisualStyleBackColor = true;
			// 
			// user_sent_lab
			// 
			this->user_sent_lab->AutoSize = true;
			this->user_sent_lab->Location = System::Drawing::Point(251, 13);
			this->user_sent_lab->Name = L"user_sent_lab";
			this->user_sent_lab->Size = System::Drawing::Size(98, 13);
			this->user_sent_lab->TabIndex = 6;
			this->user_sent_lab->Text = L"User\'s Sentinel Key";
			this->user_sent_lab->Click += gcnew System::EventHandler(this, &Form1::label1_Click_1);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(251, 109);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(70, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Current Timer";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click_2);
			// 
			// beginKeyLabel
			// 
			this->beginKeyLabel->AutoSize = true;
			this->beginKeyLabel->Location = System::Drawing::Point(12, 54);
			this->beginKeyLabel->Name = L"beginKeyLabel";
			this->beginKeyLabel->Size = System::Drawing::Size(55, 13);
			this->beginKeyLabel->TabIndex = 8;
			this->beginKeyLabel->Text = L"Begin Key";
			this->beginKeyLabel->Click += gcnew System::EventHandler(this, &Form1::label2_Click_1);
			// 
			// beginKeyText
			// 
			this->beginKeyText->Location = System::Drawing::Point(85, 54);
			this->beginKeyText->Name = L"beginKeyText";
			this->beginKeyText->Size = System::Drawing::Size(100, 20);
			this->beginKeyText->TabIndex = 9;
			this->beginKeyText->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::beginKeyText_KeyDown);
			// 
			// beginBut
			// 
			this->beginBut->Location = System::Drawing::Point(193, 50);
			this->beginBut->Name = L"beginBut";
			this->beginBut->Size = System::Drawing::Size(52, 23);
			this->beginBut->TabIndex = 10;
			this->beginBut->Text = L"Confirm";
			this->beginBut->UseVisualStyleBackColor = true;
			this->beginBut->Click += gcnew System::EventHandler(this, &Form1::beginBut_Click);
			// 
			// userBeginLabel
			// 
			this->userBeginLabel->AutoSize = true;
			this->userBeginLabel->Location = System::Drawing::Point(254, 54);
			this->userBeginLabel->Name = L"userBeginLabel";
			this->userBeginLabel->Size = System::Drawing::Size(87, 13);
			this->userBeginLabel->TabIndex = 11;
			this->userBeginLabel->Text = L"User\'s Begin Key";
			// 
			// fnLabel
			// 
			this->fnLabel->AutoSize = true;
			this->fnLabel->Location = System::Drawing::Point(474, 19);
			this->fnLabel->Name = L"fnLabel";
			this->fnLabel->Size = System::Drawing::Size(57, 13);
			this->fnLabel->TabIndex = 12;
			this->fnLabel->Text = L"File Name:";
			// 
			// fnBox
			// 
			this->fnBox->Location = System::Drawing::Point(538, 19);
			this->fnBox->Name = L"fnBox";
			this->fnBox->Size = System::Drawing::Size(100, 20);
			this->fnBox->TabIndex = 13;
			// 
			// fnBut
			// 
			this->fnBut->Location = System::Drawing::Point(645, 19);
			this->fnBut->Name = L"fnBut";
			this->fnBut->Size = System::Drawing::Size(75, 23);
			this->fnBut->TabIndex = 14;
			this->fnBut->Text = L"Confirm";
			this->fnBut->UseVisualStyleBackColor = true;
			this->fnBut->Click += gcnew System::EventHandler(this, &Form1::fnBut_Click);
			// 
			// runBut
			// 
			this->runBut->Location = System::Drawing::Point(330, 242);
			this->runBut->Name = L"runBut";
			this->runBut->Size = System::Drawing::Size(107, 35);
			this->runBut->TabIndex = 15;
			this->runBut->Text = L"Run Macro";
			this->runBut->UseVisualStyleBackColor = true;
			this->runBut->Click += gcnew System::EventHandler(this, &Form1::runBut_Click);
			// 
			// presetLabel
			// 
			this->presetLabel->AutoSize = true;
			this->presetLabel->Location = System::Drawing::Point(474, 56);
			this->presetLabel->Name = L"presetLabel";
			this->presetLabel->Size = System::Drawing::Size(67, 13);
			this->presetLabel->TabIndex = 16;
			this->presetLabel->Text = L"Load Preset:";
			// 
			// presetBox
			// 
			this->presetBox->Location = System::Drawing::Point(538, 53);
			this->presetBox->Name = L"presetBox";
			this->presetBox->Size = System::Drawing::Size(100, 20);
			this->presetBox->TabIndex = 17;
			// 
			// presetBut
			// 
			this->presetBut->Location = System::Drawing::Point(645, 50);
			this->presetBut->Name = L"presetBut";
			this->presetBut->Size = System::Drawing::Size(75, 23);
			this->presetBut->TabIndex = 18;
			this->presetBut->Text = L"Confirm";
			this->presetBut->UseVisualStyleBackColor = true;
			this->presetBut->Click += gcnew System::EventHandler(this, &Form1::presetBut_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(802, 422);
			this->Controls->Add(this->presetBut);
			this->Controls->Add(this->presetBox);
			this->Controls->Add(this->presetLabel);
			this->Controls->Add(this->runBut);
			this->Controls->Add(this->fnBut);
			this->Controls->Add(this->fnBox);
			this->Controls->Add(this->fnLabel);
			this->Controls->Add(this->userBeginLabel);
			this->Controls->Add(this->beginBut);
			this->Controls->Add(this->beginKeyText);
			this->Controls->Add(this->beginKeyLabel);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->user_sent_lab);
			this->Controls->Add(this->timerBut);
			this->Controls->Add(this->timerLabel);
			this->Controls->Add(this->timerBox);
			this->Controls->Add(this->sentinelBut);
			this->Controls->Add(this->sentinelBox);
			this->Controls->Add(this->sentinelLabel);
			this->Name = L"Form1";
			this->Text = L"Macro Maker";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	

	
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) { //sentinel box
		
	}
	
	private: System::Void textBox1_KeyDown(System::Object^ /*sender*/, System::Windows::Forms::KeyEventArgs^ e) {
		
		curSentKey = e->KeyCode;
		//can update the textbox for whatever key was pressed
		
	}
	private: System::Void Form1_MouseDown(System::Object^ ender, MouseEventArgs^ e) {
		int x_pos = 0;
		int y_pos = 0;
		String^ mb_down;
		x_pos = e->X; // maybe we should ue string format and change everytyhing that way! holy shit this fixes soooo much....
		y_pos = e->Y;
		mb_down = e->Button.ToString();
		
	}

	private: System::Void Form1_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		curKeyUp = e->KeyCode;
		if (isTracking) {
		//	ku_timeDiff = clock() - ;
		}

	}
	private: System::Void Form1_KeyDown(System::Object^ /*sender*/, System::Windows::Forms::KeyEventArgs^ e) {
		
		String^ keyStr = "";
		curKeyDown = e->KeyCode; //tracks all of the user's keyboard inputs.

		if (curKeyDown == sentKey) //end tracking
			isTracking = false;

		if (isTracking) { //makes sure the user has entered a name for the text file.

		//	kd_timeDiff = difftime(clock(), lastTime); //gets current time and subtracts it from the last time to get how long between keys.
			kd_timeDiff = difftime(clock(), lastTime);
			keyStr = String::Format("{0}", e->KeyCode.ToString());
			track.writeKey(0,kd_timeDiff, keyStr);
			lastTime = clock();
		}

		if (curKeyDown == begKey) { // If the user presses the sentinel key, begin tracking. This needs to be a single press though.
			isTracking = true;
		//set time to current. 
			curTime = clock();
			lastTime = clock();
		//begin tracking
		}


		

	}
	
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
		//sentinelLabel->Text = sentKey.ToString();
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		if (curSentKey != Keys::None) {
			sentKey = curSentKey;
			user_sent_lab->Text = sentKey.ToString();
		}

	}
	private: System::Void textBox1_TextChanged_1(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {

	}
	private: System::Void label1_Click_1(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label1_Click_2(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label2_Click_1(System::Object^  sender, System::EventArgs^  e) {
	}
	
	private: System::Void beginKeyText_KeyDown(System::Object^  /*sender*/, System::Windows::Forms::KeyEventArgs^  e) {
		curBegKey = e->KeyCode; //Set temporary key
	}
	private: System::Void beginBut_Click(System::Object^  sender, System::EventArgs^  e) {
		if (curBegKey != Keys::None) { // make sure key isn't empty
			begKey = curBegKey;
			userBeginLabel->Text = begKey.ToString(); // Update current beg key text.
		}
	}
	private: System::Void fnBut_Click(System::Object^  sender, System::EventArgs^  e) {
		//add if fo
		String^ tempStr = fnBox->Text + ".txt";
		track.setFileName(tempStr);
		Diagnostics::Debug::WriteLine(tempStr);
		//check the text field
		//determine if valid file name.
		//if Not, print something like an error dialog. figure it out.
	
	}
	private: System::Void runBut_Click(System::Object^  sender, System::EventArgs^  e) {
			//track.beginTracking();
			track.createFile();
		
	}

private: System::Void presetBut_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ presetName = presetBox->Text;
	if (!presetName->Equals(NULL)) {
		DateTime^ dt = DateTime::Now;
		Debug::WriteLine(dt->Millisecond);
		track.runMacro(presetName);
		
	}

}
};
}
