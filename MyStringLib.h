#pragma once
#include<iostream> 
#include<vector>
using namespace std;
class clsString
{
private:
	string _Value;

public:

	//Constuctors 
	clsString() {
		_Value = "";
	}
	clsString(string value) {
		_Value = value;
	}


	//Set and Get Value
	void SetValue(string value) {
		_Value = value;
	}
	string GetValue() {
		return _Value;
	}

	_declspec(property(get = GetValue, put = SetValue))string Value;

	//Count Words in String
	static short CountWord(string S1) {
		string word = "";//to store the corrent word 
		string delim = " ";
		short pas = 0;
		short counter = 0;
		while ((pas = S1.find(delim)) != std::string::npos) {

			word = S1.substr(0, pas);
			if (word != "") {
				counter++;
			}
			S1.erase(0, pas + delim.length());//erase the last word to go to the next one
		}
		if (S1 != "") {
			counter++;
		}
		return counter;


	}
	short Countword() {

		return CountWord(_Value);

	}

	//Split words of the string in put them in vector
	static vector <string> SplitString(string S1, string delim = " ") {
		string sWord = "";
		short pos = 0;
		vector <string> vWords;

		while ((pos = S1.find(delim)) != std::string::npos) {
			sWord = S1.substr(0, pos);
			if (sWord != "") {

				vWords.push_back(sWord);

			}

			S1.erase(0, pos + delim.length());

		}
		if (S1 != "") {
			vWords.push_back(S1);
		}

		return vWords;
	}
	vector <string> SplitString(string delim = " ") {

		return SplitString(_Value, delim);


	}

	// Upper the whole string
	static string UpperString(string S1) {

		for (short i = 0; i < S1.length(); i++) {
			S1[i] = toupper(S1[i]);

		}


		return S1;
	}
	void UpperString() {

		_Value = UpperString(_Value);

	}
	//Lower the Whole String
	static string LowerString(string S1) {

		for (short i = 0; i < S1.length(); i++) {
			S1[i] = tolower(S1[i]);

		}


		return S1;
	}
	void LowerString() {

		_Value = LowerString(_Value);
	}


	// Upper Or Lower the first Letter of every Word
	static string UpperFirstLetterOfEachWord(string S1) {
		bool isfirstletter = true;

		for (short i = 0; i < S1.length(); i++) {
			if (S1[i] != ' ' && isfirstletter) {
				S1[i] = toupper(S1[i]);
			}

			isfirstletter = (S1[i] == ' ' ? true : false);

		}
		return S1;



	}
	void  UpperFirstLetterOfEachWord() {

		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstCaseOfEachWord(string S1) {

		bool isfirstletter = true;

		for (short i = 0; i < S1.length(); i++) {
			if (S1[i] != ' ' && isfirstletter) {
				S1[i] = tolower(S1[i]);
			}

			isfirstletter = (S1[i] == ' ' ? true : false);

		}
		return S1;


	}
	void LowerFirstCaseOfEachWord() {

		_Value = LowerFirstCaseOfEachWord(_Value);
	}

	//invert cases
	static char InvertLetter(char letter) {

		return isupper(letter) ? tolower(letter) : toupper(letter);

	}

	static string InvertStringCases(string S1) {
		for (short i = 0; i < S1.length(); i++) {

			S1[i] = InvertLetter(S1[i]);

		}

		return S1;
	}

	void InvertStringCases() {
		_Value = InvertStringCases(_Value);
	}

	//Count functions 
	enum WhatToCount {
		uppertype = 1, lowertype = 2, all = 3
	};
	static short CountLetters(string S1, WhatToCount Type = WhatToCount::all) {
		short count = 0;
		if (Type == WhatToCount::all) {

			return S1.length();
		}
		for (short i = 0; i < S1.length(); i++) {

			if (Type == WhatToCount::lowertype && islower(S1[i]))
				count++;

			if (Type == WhatToCount::uppertype && isupper(S1[i]))
				count++;




		}

		return count;

	}
	short CountLetters(WhatToCount Type = WhatToCount::all) {
		return CountLetters(_Value, Type);
	}

	static short CountUpperLetters(string S1) {
		short count = 0;
		for (short i = 0; i < S1.length(); i++) {
			if (isupper(S1[i])) {
				count++;
			}


		}

		return count;
	}
	short CountUpperLetters() {
		return CountUpperLetters(_Value);

	}

	static short CountLowerLetters(string S1) {
		short count = 0;
		for (short i = 0; i < S1.length(); i++) {
			if (islower(S1[i])) {
				count++;
			}


		}

		return count;
	}
	short CountLowerLetters() {

		return CountLowerLetters(_Value);

	}

	static short CountSpicificLetter(string S1, char Letter, bool MatchCase = true) {
		short count = 0;
		for (short i = 0; i < S1.length(); i++) {
			if (MatchCase) {
				toupper(Letter) == toupper(S1[i]) ? count++ : false;
			}
			else {
				(Letter == S1[i]) ? count++ : false;
			}
		}

	}
	short CountSpicificLetter(char Letter, bool MatchCase = true) {
		return CountSpicificLetter(_Value, Letter, MatchCase);
	}

	//to Check if the letter is vowel ANd Count How Many Vowels In String 
	static bool IsVowel(char letter) {

		return (tolower(letter) == 'a' || tolower(letter) == 'e' || tolower(letter) == 'o' || tolower(letter) == 'u' ||
			tolower(letter) == 'i' || tolower(letter) == 'y');

	}
	static short CountVowels(string S1) {
		short counter = 0;
		for (short i = 0; i < S1.length(); i++) {
			if (IsVowel(S1[i])) {
				counter++;
			}

		}
		return counter;
	}
	short CountVowels() {

		return  CountVowels(_Value);

	}


	static string JoinString(string arr[], short length, string delim = " ") {
		string S1 = "";
		for (short i = 0; i < length; i++) {
			S1 = S1 + arr[i] + " ";
		}

		return S1;
	}
	static string JoinString(vector<string> vWords, string delim = " ") {
		string S1 = "";
		for (short i = 0; i < vWords.size(); i++) {
			S1 = S1 + vWords[i] + delim;
		}

		return S1;

	}


	//Trim Fonctions :
	static string TrimLeft(string S1) {

		short counter = 0;
		while (S1[counter] == ' ') {
			counter++;

		}

		S1.erase(0, counter);
		return S1;
	}
	static string TrimRight(string S1) {
		short counter = S1.length() - 1;
		while (S1[counter] == ' ') {
			counter--;
		}

		S1.erase(counter + 1, S1.length() - 1);
		return S1;
	}
	static string Trim(string S1) {

		S1 = TrimLeft(S1);
		S1 = TrimRight(S1);

		return S1;
	}
	string Trim() {
		return Trim(_Value);
	}

	//Revers Words of string
	//to revers the words first we use split and then we use pointers to read the vector from the end 'vector iterators'


	short Length() {

		return _Value.length();

	}

};
