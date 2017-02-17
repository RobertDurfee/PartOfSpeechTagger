#ifndef PART_OF_SPEECH_TAGGER_HEADER
#define PART_OF_SPEECH_TAGGER_HEADER

#include "HiddenMarkovModel.h"
#include <string>
#include <sstream>
#include <mysql.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

string ToUpperCase(string input)
{
	int length = (int)input.length();

	stringstream output;

	int i = -1;
	while (++i < (int)input.length())
	{
		if (input[i] >= 'a' && input[i] <= 'z')
			output << (char)(input[i] - ' ');
		else
			output << (char)input[i];
	}

	return output.str();
}
string ToLowerCase(string input)
{
	stringstream output;

	int i = -1;
	while (++i < (int)input.length())
	{
		if (input[i] >= 'A' && input[i] <= 'Z')
			output << (char)(input[i] + ' ');
		else
			output << (char)input[i];
	}

	return output.str();
}
void ToLowerCase(string * input)
{
	stringstream output;

	int i = -1;
	while (++i < (int)input->length())
	{
		if ((*input)[i] >= 'A' && (*input)[i] <= 'Z')
			output << (char)((*input)[i] + ' ');
		else
			output << (char)(*input)[i];
	}

	input->assign(output.str());
}
string InsertToString(string input, ...)
{
	int index = -1, result, count = 0;
	while ((index = input.find("%s", ++index)) != -1)
		count++;

	va_list List;
	va_start(List, input);

	for (int i = 0; i < count; i++)
	{
		input = input.erase((result = input.find("%s")), 2);
		input = input.insert(result, va_arg(List, char *));
	}

	va_end(List);

	return input;
}
string CharacterVectorToString(vector<char> Input)
{
	stringstream ss;

	for (int i = 0; i < (int)Input.size(); i++)
		ss << Input[i];

	return ss.str();
}
bool VectorContains(vector<string> container, string contains)
{
	for (int i = 0; i < (int)container.size(); i++)
		if (container[i] == contains) return true;
	return false;
}

struct SQLWord
{
	SQLWord(int, string, string, int, float);
	SQLWord(string, string, string, string, string);

	int ID;
	string Word;
	string PartOfSpeechString;
	int PartOfSpeechConstant;
	float Percentage;
};
SQLWord::SQLWord(int ID, string Word, string PartOfSpeechString, int PartOfSpeechConstant, float Percentage)
{
	this->ID = ID;
	this->Word = Word;
	this->PartOfSpeechString = PartOfSpeechString;
	this->PartOfSpeechConstant = PartOfSpeechConstant;
	this->Percentage = Percentage;
}
SQLWord::SQLWord(string ID, string Word, string PartOfSpeechString, string PartOfSpeechConstant, string Percentage)
{
	stringstream ss;

	ss << ID; ss >> this->ID; ss.str(""); ss.clear();
	this->Word = Word;
	this->PartOfSpeechString = PartOfSpeechString;
	ss << PartOfSpeechConstant; ss >> this->PartOfSpeechConstant; ss.str(""); ss.clear();
	ss << Percentage; ss >> this->Percentage;
}

struct SQLAdjacentWord
{
	SQLAdjacentWord(int, string, string, int, int, float);
	SQLAdjacentWord(string, string, string, string, string, string);

	int ID;
	string FirstPartOfSpeechString;
	string SecondPartOfSpeechString;
	int FirstPartOfSpeechConstant;
	int SecondPartOfSpeechConstant;
	float Percentage;
};
SQLAdjacentWord::SQLAdjacentWord(int ID, string FirstPartOfSpeechString, string SecondPartOfSpeechString, int FirstPartOfSpeechConstant, int SecondPartOfSpeechConstant, float Percentage)
{
	this->ID = ID;
	this->FirstPartOfSpeechString = FirstPartOfSpeechString;
	this->SecondPartOfSpeechString = SecondPartOfSpeechString;
	this->FirstPartOfSpeechConstant = FirstPartOfSpeechConstant;
	this->SecondPartOfSpeechConstant = SecondPartOfSpeechConstant;
	this->Percentage = Percentage;
}
SQLAdjacentWord::SQLAdjacentWord(string ID, string FirstPartOfSpeechString, string SecondPartOfSpeechString, string FirstPartOfSpeechConstant, string SecondPartOfSpeechConstant, string Percentage)
{
	stringstream ss;
	ss << ID; ss >> this->ID; ss.str(""); ss.clear();
	this->FirstPartOfSpeechString = FirstPartOfSpeechString;
	this->SecondPartOfSpeechString = SecondPartOfSpeechString;
	ss << FirstPartOfSpeechConstant; ss >> this->FirstPartOfSpeechConstant; ss.str(""); ss.clear();
	ss << SecondPartOfSpeechConstant; ss >> this->SecondPartOfSpeechConstant; ss.str(""); ss.clear();
	ss << Percentage; ss >> this->Percentage;
}

struct SQLFirstWord
{
	SQLFirstWord(int, string, int, float);
	SQLFirstWord(string, string, string, string);

	int ID;
	string PartOfSpeechString;
	int PartOfSpeechConstant;
	float Percentage;
};
SQLFirstWord::SQLFirstWord(int ID, string PartOfSpeechString, int PartOfSpeechConstant, float Percentage)
{
	this->ID = ID;
	this->PartOfSpeechString = PartOfSpeechString;
	this->PartOfSpeechConstant = PartOfSpeechConstant;
	this->Percentage = Percentage;
}
SQLFirstWord::SQLFirstWord(string ID, string PartOfSpeechString, string PartOfSpeechConstant, string Percentage)
{
	stringstream ss;

	ss << ID; ss >> this->ID; ss.str(""); ss.clear();
	this->PartOfSpeechString = PartOfSpeechString;
	ss << PartOfSpeechConstant; ss >> this->PartOfSpeechConstant; ss.str(""); ss.clear();
	ss << Percentage; ss >> this->Percentage;
}

struct TaggedWord
{
	TaggedWord(string, string);

	string Word;
	string Tag;
};
TaggedWord::TaggedWord(string Word, string Tag)
{
	this->Word = Word;
	this->Tag = Tag;
}

struct Word
{
	Word(string, string);
	void IncreaseFrequency();

	string word;
	string tag;
	int frequency;
};
Word::Word(string word, string tag)
{
	this->word = word;
	this->tag = tag;
	this->frequency = 1;
}
void Word::IncreaseFrequency()
{
	this->frequency++;
}

struct AdjacentWord
{
	AdjacentWord(string, string);
	void IncreaseFrequency();

	string firsttag;
	string secondtag;
	int frequency;
};
AdjacentWord::AdjacentWord(string firsttag, string secondtag)
{
	this->firsttag = firsttag;
	this->secondtag = secondtag;
	this->frequency = 1;
}
void AdjacentWord::IncreaseFrequency()
{
	this->frequency++;
}

struct FirstWord
{
	FirstWord(string);
	void IncreaseFrequency();

	string tag;
	int frequency;
};
FirstWord::FirstWord(string tag)
{
	this->tag = tag;
	this->frequency = 1;
}
void FirstWord::IncreaseFrequency()
{
	this->frequency++;
}

#define PART_OF_SPEECH_WORDS_TABLE			0x1
#define PART_OF_SPEECH_ADJACENT_WORDS_TABLE 0x2
#define PART_OF_SPEECH_FIRST_WORDS_TABLE	0x3

class PartOfSpeechTagger
{
public:
	PartOfSpeechTagger();
	PartOfSpeechTagger(string, string, string);
	PartOfSpeechTagger(string, string, string, string);

	string ParseToString(string, bool);
	vector<string> ParseToVector(string, bool);

	void InitializeDatabase(string);

private:
	MYSQL * databaseConnectionHandle;

	bool Connect(string, string, string);
	void Disconnect();

	bool Insert(void *, int);
	vector<void *> Query(string, int);

	int PartOfSpeechConstant(string);
	string PartOfSpeech(string);
};

PartOfSpeechTagger::PartOfSpeechTagger(string server, string user, string password)
{
	this->Connect(server, user, password);
}
PartOfSpeechTagger::PartOfSpeechTagger(string brownCorpusDirectory, string server, string user, string password)
{
	this->Connect(server, user, password);

	this->InitializeDatabase(brownCorpusDirectory);
}
PartOfSpeechTagger::PartOfSpeechTagger()
{
	this->Connect("104.154.17.90", "root", "cgCG123!@#");
}

string PartOfSpeechTagger::ParseToString(string input, bool abbreviated = true)
{
	vector<string> StateSequence = this->ParseToVector(input, abbreviated);

	//Print the State Sequence
	stringstream output;
	for (int i = 0; i < (int)StateSequence.size(); i++)
		output << StateSequence[i] << " ";

	return output.str();
}
vector<string> PartOfSpeechTagger::ParseToVector(string input, bool abbreviated = true)
{
	vector<string> error;
	error.push_back("Unexpected FirstWords SQL Query Result.");

	ToLowerCase(&input);
	for (int i = 0; i < (int)input.length(); i++)
		if (input[i] == ',' || input[i] == ';' || input[i] == ':' || input[i] == '.' || input[i] == '!' || input[i] == '?')
			input.insert(i++, " ");

	//Sentence to be Tagged 
	vector<string> ObservationSequence;

	int index1 = 0, index2 = 0;
	while ((index2 = input.find(' ', index1)) != -1)
	{
		ObservationSequence.push_back(input.substr(index1, index2 - index1));
		index1 = index2 + 1;
	}

	ObservationSequence.push_back(input.substr(index1, input.length() - index1));

	//All Possible States that Match the Observations
	vector<string> States;
	for (int j = 0; j < (int)ObservationSequence.size(); j++)
	{
		vector<void *> words = this->Query(InsertToString("SELECT * FROM `LanguageData`.`Words` WHERE `Word` = '%s'", ObservationSequence[j].c_str()), PART_OF_SPEECH_WORDS_TABLE);
		if (words.size() == 0)
			return error;
		for (int i = 0; i < (int)words.size(); i++)
			if (!VectorContains(States, ((SQLWord *)words[i])->PartOfSpeechString))
				States.push_back(((SQLWord *)words[i])->PartOfSpeechString);
	}

	//All Observations Without Repeats
	vector<string> Observations;
	for (int i = 0; i < (int)ObservationSequence.size(); i++)
		if (!VectorContains(Observations, ObservationSequence[i]))
			Observations.push_back(ObservationSequence[i]);

	//Initialize Hidden Markov Model
	HiddenMarkovModel Sentence(States, Observations);

	//Initialize the Initial Matrix
	for (int i = 0; i < (int)States.size(); i++)
	{
		vector<void *> firstWords = this->Query(InsertToString("SELECT * FROM `LanguageData`.`FirstWords` WHERE `PartOfSpeechString` = '%s'", States[i].c_str()), PART_OF_SPEECH_FIRST_WORDS_TABLE);
		if ((int)firstWords.size() == 1)
			Sentence.Initial[States[i]] = ((SQLAdjacentWord *)firstWords[0])->Percentage;
		else if ((int)firstWords.size() == 0)
			Sentence.Initial[States[i]] = 0;
		else
			return error;
	}

	//Initialize the Emission Matrix
	for (int i = 0; i < (int)States.size(); i++)
	{
		for (int j = 0; j < (int)Observations.size(); j++)
		{
			vector<void *> words = this->Query(InsertToString("SELECT * FROM `LanguageData`.`Words` WHERE `PartOfSpeechString` = '%s' AND `Word` = '%s'", States[i].c_str(), Observations[j].c_str()), PART_OF_SPEECH_WORDS_TABLE);

			if ((int)words.size() == 1)
				Sentence.Emission[States[i]][Observations[j]] = ((SQLWord *)words[0])->Percentage;
			else if ((int)words.size() == 0)
				Sentence.Emission[States[i]][Observations[j]] = 0;
			else
				return error;
		}
	}

	//Initialize the Transition Matrix
	for (int i = 0; i < (int)States.size(); i++)
	{
		for (int j = 0; j < (int)States.size(); j++)
		{
			vector<void *> adjacentWords = this->Query(InsertToString("SELECT * FROM `LanguageData`.`AdjacentWords` WHERE `FirstPartOfSpeechString` = '%s' AND `SecondPartOfSpeechString` = '%s'", States[i].c_str(), States[j].c_str()), PART_OF_SPEECH_ADJACENT_WORDS_TABLE);
			if ((int)adjacentWords.size() == 1)
				Sentence.Transition[States[i]][States[j]] = ((SQLAdjacentWord *)adjacentWords[0])->Percentage;
			else if ((int)adjacentWords.size() == 0)
				Sentence.Transition[States[i]][States[j]] = 0;
			else
				return error;
		}
	}

	//Normalize the Matrices So They All Add Up to 100 percent
	Sentence.Normalize(HIDDEN_MARKOV_MODEL_INITIAL_MATRIX | HIDDEN_MARKOV_MODEL_EMISSION_MATRIX | HIDDEN_MARKOV_MODEL_TRANSITION_MATRIX);

	//Run the Viterbi Algorithm to Assign States to Observations
	vector<string> StateSequence = Sentence.Viterbi(ObservationSequence);

	if (!abbreviated)
		for (int i = 0; i < (int)StateSequence.size(); i++)
			StateSequence[i] = this->PartOfSpeech(StateSequence[i]);

	return StateSequence;
}

void PartOfSpeechTagger::InitializeDatabase(string brownCorpusDirectory)
{
	vector<vector<TaggedWord>> TaggedWords;

	cout << "(Step 1 of 4) Reading Files..." << endl;

	for (int i = 0; i < 500; i++)
	{
		stringstream ss;

		ss << brownCorpusDirectory << "brown (" << i + 1 << ")" << '\0';

		ifstream ifile(ss.str());

		string fileData;
		fileData.assign(istreambuf_iterator<char>(ifile), istreambuf_iterator<char>());

		//Remove Headings
		int index = -1;
		while ((index = fileData.find("-hl", ++index)) != -1)
			if (fileData[index - 2] == '/' || fileData[index - 3] == '/' || fileData[index - 4] == '/' || fileData[index - 5] == '/')
			{
				int tempIndex = index;
				while (index != 0 && fileData[--index] != ' ');
				fileData.erase(index, tempIndex - index + 3);
			}

		//Remove title designations
		index = 0;
		while ((index = fileData.find("-tl", index)) != -1)
			fileData.erase(index, 3);
		index = 0;
		while ((index = fileData.find("-nc", index)) != -1)
			fileData.erase(index, 3);

		//Remove tabs and new lines
		index = 0;
		while ((index = fileData.find("\t", index)) != -1)
			fileData.erase(index, 1);
		index = 0;
		while ((index = fileData.find("\n", index)) != -1)
			fileData.erase(index, 1);

		//Split passage into sentences
		int firstIndex = -2, secondIndex = 0;
		vector<string> sentences;
		while ((secondIndex = fileData.find("/.", firstIndex += 2)) != -1)
		{
			sentences.push_back(fileData.substr(firstIndex, secondIndex - firstIndex + strlen("/.")));
			firstIndex = secondIndex;
		}

		//Split sentences into words
		for (int sentence = 0; sentence < (int)sentences.size(); sentence++)
		{
			TaggedWords.push_back(vector<TaggedWord>());

			for (int character = 0; character < (int)sentences[sentence].size(); character++)
				if (sentences[sentence][character] == '/')
				{
					//Back track until a space or beginning of string is encountered
					int tempIndex = character - 1;
					vector<char> tempWord;
					while (tempIndex > -1 && sentences[sentence][tempIndex] != ' ')
						tempWord.insert(tempWord.begin(), sentences[sentence][tempIndex--]);

					//Forward track until a space or end of string is encountered
					tempIndex = character + 1;
					vector<char> tempTag;
					while (tempIndex < (int)sentences[sentence].size() && sentences[sentence][tempIndex] != ' ')
						tempTag.push_back(sentences[sentence][tempIndex++]);

					//Save this as an element in the 'words' vector of vectors
					TaggedWords[TaggedWords.size() - 1].push_back(TaggedWord(ToLowerCase(CharacterVectorToString(tempWord)), ToLowerCase(CharacterVectorToString(tempTag))));
				}
		}
	}

	vector<Word> Words;
	vector<AdjacentWord> AdjacentWords;
	vector<FirstWord> FirstWords;

	cout << "(Step 2 of 4) Parsing Words..." << endl;

	for (int CurrentSentenceIndex = 0; CurrentSentenceIndex < (int)TaggedWords.size(); CurrentSentenceIndex++)
	{
		//Loop through all FirstWords
		for (int z = 0; z < (int)FirstWords.size(); z++)
			//If this tag appeared before,
			if (FirstWords[z].tag == TaggedWords[CurrentSentenceIndex][0].Tag)
			{
				//Increase its frequency,
				FirstWords[z].IncreaseFrequency();
				//And DO NOT add a duplicate
				goto SKIP_FIRST_WORD_PUSH_BACK;
			}

		//Add the newly encountered FirstWord combination
		FirstWords.push_back(FirstWord(TaggedWords[CurrentSentenceIndex][0].Tag));

	SKIP_FIRST_WORD_PUSH_BACK:

		//Loop through all Words
		for (int z = 0; z < (int)Words.size(); z++)
			//If this combination appeard before,
			if (Words[z].word == TaggedWords[CurrentSentenceIndex][0].Word && Words[z].tag == TaggedWords[CurrentSentenceIndex][0].Tag)
			{
				//Increase its frequency,
				Words[z].IncreaseFrequency();
				//And DO NOT add a duplicate
				goto SKIP_WORDS_PUSH_BACK_1;
			}

		//Add the newly encountered Word combination
		Words.push_back(Word(TaggedWords[CurrentSentenceIndex][0].Word, TaggedWords[CurrentSentenceIndex][0].Tag));

	SKIP_WORDS_PUSH_BACK_1:

		//Initialize the previous word
		TaggedWord PreviousWord(TaggedWords[CurrentSentenceIndex][0]);

		//Loop through all words in the sentence starting at 1 because word 0 has already been added and initialized as previous word
		for (int CurrentWordIndex = 1; CurrentWordIndex < (int)TaggedWords[CurrentSentenceIndex].size(); CurrentWordIndex++)
		{
			//Loop through all Words
			for (int z = 0; z < (int)Words.size(); z++)
				//If this combination appeared before,
				if (Words[z].word == TaggedWords[CurrentSentenceIndex][CurrentWordIndex].Word && Words[z].tag == TaggedWords[CurrentSentenceIndex][CurrentWordIndex].Tag)
				{
					//Increase its frequency,
					Words[z].IncreaseFrequency();
					//And DO NOT add a duplicate
					goto SKIP_WORDS_PUSH_BACK_2;
				}

			//Add the newly encountered Word combination
			Words.push_back(Word(TaggedWords[CurrentSentenceIndex][CurrentWordIndex].Word, TaggedWords[CurrentSentenceIndex][CurrentWordIndex].Tag));

		SKIP_WORDS_PUSH_BACK_2:

			//Loop through all AdjacentWords
			for (int z = 0; z < (int)AdjacentWords.size(); z++)
				//If this combination appeared before,
				if (AdjacentWords[z].firsttag == PreviousWord.Tag && AdjacentWords[z].secondtag == TaggedWords[CurrentSentenceIndex][CurrentWordIndex].Tag)
				{
					//Increase its frequency,
					AdjacentWords[z].IncreaseFrequency();
					//And DO NOT add a duplicate
					goto SKIP_ADJACENT_WORDS_PUSH_BACK;
				}

			//Add the newly encountered AdjacentWords combination
			AdjacentWords.push_back(AdjacentWord(PreviousWord.Tag, TaggedWords[CurrentSentenceIndex][CurrentWordIndex].Tag));

		SKIP_ADJACENT_WORDS_PUSH_BACK:

			//Replace the previous word with the current word
			PreviousWord.Tag = TaggedWords[CurrentSentenceIndex][CurrentWordIndex].Tag;
			PreviousWord.Word = TaggedWords[CurrentSentenceIndex][CurrentWordIndex].Word;
		}
	}

	//Free up some memory
	TaggedWords.clear();

	vector<SQLWord> SQLWords;
	vector<SQLAdjacentWord> SQLAdjacentWords;
	vector<SQLFirstWord> SQLFirstWords;

	cout << "(Step 3 of 4) Calculating Percentages..." << endl;

	//Loop through all words
	for (int i = 0; i < (int)Words.size(); i++)
	{
		vector<Word> TempWords;

		//Make sure this word wasn't encountered already
		for (int z = 0; z < (int)SQLWords.size(); z++)
			if (SQLWords[z].Word == Words[i].word)
				goto SKIP_WORD;

		//Populate a vector of all words with their particular tags
		for (int j = 0; j < (int)Words.size(); j++)
			if (Words[i].word == Words[j].word)
				TempWords.push_back(Words[j]);

		//Determine the sum of all the frequencies
		int TotalFrequencyOfWord = 0;
		for (int z = 0; z < (int)TempWords.size(); z++)
			TotalFrequencyOfWord += TempWords[z].frequency;

		//Copy the data into the SQL format with the correct distribution
		for (int z = 0; z < (int)TempWords.size(); z++)
			SQLWords.push_back(SQLWord(NULL, TempWords[z].word, TempWords[z].tag, PartOfSpeechConstant(TempWords[z].tag), (float)TempWords[z].frequency / (float)TotalFrequencyOfWord));

	SKIP_WORD:;
	}

	for (int i = 0; i < (int)AdjacentWords.size(); i++)
	{
		vector<AdjacentWord> TempAdjacentWords;

		//Make sure these adjacent words weren't encountered already
		for (int z = 0; z < (int)SQLAdjacentWords.size(); z++)
			if (SQLAdjacentWords[z].FirstPartOfSpeechString == AdjacentWords[i].firsttag)
				goto SKIP_ADJACENT_WORD;

		//Populate a vector of all adjacent words with their particular tags
		for (int j = 0; j < (int)AdjacentWords.size(); j++)
			if (AdjacentWords[i].firsttag == AdjacentWords[j].firsttag)
				TempAdjacentWords.push_back(AdjacentWords[j]);

		//Determine the sum of all the frequencies
		int TotalFrequecyOfAdjacentWords = 0;
		for (int z = 0; z < (int)TempAdjacentWords.size(); z++)
			TotalFrequecyOfAdjacentWords += TempAdjacentWords[z].frequency;

		//Copy the data into the SQL format with the correct distribution
		for (int z = 0; z < (int)TempAdjacentWords.size(); z++)
			SQLAdjacentWords.push_back(SQLAdjacentWord(NULL, TempAdjacentWords[z].firsttag, TempAdjacentWords[z].secondtag, PartOfSpeechConstant(TempAdjacentWords[z].firsttag), PartOfSpeechConstant(TempAdjacentWords[z].secondtag), (float)TempAdjacentWords[z].frequency / (float)TotalFrequecyOfAdjacentWords));

	SKIP_ADJACENT_WORD:;
	}

	//Determine the sum of all frequencies of FirstWords
	int TotalFrequencyOfFirstWord = 0;
	for (int i = 0; i < (int)FirstWords.size(); i++)
		TotalFrequencyOfFirstWord += FirstWords[i].frequency;

	//Copy the data into the SQL format with the correct distribution
	for (int i = 0; i < (int)FirstWords.size(); i++)
		SQLFirstWords.push_back(SQLFirstWord(NULL, FirstWords[i].tag, PartOfSpeechConstant(FirstWords[i].tag), (float)FirstWords[i].frequency / (float)TotalFrequencyOfFirstWord));

	cout << "(Step 4 of 4) Adding Data to the Database..." << endl;

	//Creating data tables in the SQL database
	mysql_query(databaseConnectionHandle, "CREATE TABLE `LanguageData`.`Words` (				\
											`ID` INT NOT NULL AUTO_INCREMENT,					\
											`Word` VARCHAR(255) NOT NULL,						\
											`PartOfSpeechString` VARCHAR(255) NOT NULL,			\
											`PartOfSpeechConstant` INT NOT NULL,				\
											`Percentage` FLOAT NOT NULL,						\
										   PRIMARY KEY(`ID`));");

	mysql_query(databaseConnectionHandle, "CREATE TABLE `LanguageData`.`FirstWords` (			\
											`ID` INT NOT NULL AUTO_INCREMENT,					\
											`PartOfSpeechString` VARCHAR(255) NOT NULL,			\
											`PartOfSpeechConstant` INT NOT NULL,				\
											`Percentage` FLOAT NOT NULL,						\
										   PRIMARY KEY(`ID`));");

	mysql_query(databaseConnectionHandle, "CREATE TABLE `LanguageData`.`AdjacentWords` (		\
											`ID` INT NOT NULL AUTO_INCREMENT,					\
											`FirstPartOfSpeechString` VARCHAR(255) NOT NULL,	\
											`SecondPartOfSpeechString` VARCHAR(255) NOT NULL,	\
											`FirstPartOfSpeechConstant` INT NOT NULL,			\
											`SecondPartOfSpeechConstant` INT NOT NULL,			\
											`Percentage` FLOAT NOT NULL,						\
										   PRIMARY KEY(`ID`));");

	//Add the data into the SQL database
	for (int i = 0; i < (int)SQLAdjacentWords.size(); i++)
		this->Insert((void *)&SQLAdjacentWords[i], PART_OF_SPEECH_ADJACENT_WORDS_TABLE);
	for (int i = 0; i < (int)SQLFirstWords.size(); i++)
		this->Insert((void *)&SQLFirstWords[i], PART_OF_SPEECH_FIRST_WORDS_TABLE);
	for (int i = 0; i < (int)SQLWords.size(); i++)
		this->Insert((void *)&SQLWords[i], PART_OF_SPEECH_WORDS_TABLE);
}

bool PartOfSpeechTagger::Connect(string server, string user, string password)
{
	this->databaseConnectionHandle = mysql_init(NULL);

	return mysql_real_connect(this->databaseConnectionHandle, server.c_str(), user.c_str(), password.c_str(), NULL, 0, NULL, 0) != NULL;
}
void PartOfSpeechTagger::Disconnect()
{
	mysql_close(this->databaseConnectionHandle);
}

bool PartOfSpeechTagger::Insert(void * value, int type)
{
	stringstream query;

	switch (type)
	{
		case PART_OF_SPEECH_WORDS_TABLE:
			query << "INSERT INTO `LanguageData`.`Words` (`Word`, `PartOfSpeechString`, `PartOfSpeechConstant`, `Percentage`) VALUES ('" << ((SQLWord *)value)->Word << "', '" << ((SQLWord *)value)->PartOfSpeechString << "', " << ((SQLWord *)value)->PartOfSpeechConstant << ", " << ((SQLWord *)value)->Percentage << ")";
			break;
		case PART_OF_SPEECH_ADJACENT_WORDS_TABLE:
			query << "INSERT INTO `LanguageData`.`AdjacentWords` (`FirstPartOfSpeechString`, `SecondPartOfSpeechString`, `FirstPartOfSpeechConstant`, `SecondPartOfSpeechConstant`, `Percentage`) VALUES ('" << ((SQLAdjacentWord *)value)->FirstPartOfSpeechString << "', '" << ((SQLAdjacentWord *)value)->SecondPartOfSpeechString << "', " << ((SQLAdjacentWord *)value)->FirstPartOfSpeechConstant << ", " << ((SQLAdjacentWord *)value)->SecondPartOfSpeechConstant << ", " << ((SQLAdjacentWord *)value)->Percentage << ")";
			break;
		case PART_OF_SPEECH_FIRST_WORDS_TABLE:
			query << "INSERT INTO `LanguageData`.`FirstWords` (`PartOfSpeechString`, `PartOfSpeechConstant`, `Percentage`) VALUES('" << ((SQLFirstWord *)value)->PartOfSpeechString << "', " << ((SQLFirstWord *)value)->PartOfSpeechConstant << ", " << ((SQLFirstWord *)value)->Percentage << ")";
			break;
		default:
			return false;
	}

	return mysql_query(this->databaseConnectionHandle, query.str().c_str()) != false;
}
vector<void *> PartOfSpeechTagger::Query(string query, int type)
{
	vector<void *> output;

	mysql_query(this->databaseConnectionHandle, query.c_str());

	MYSQL_RES * result = mysql_store_result(databaseConnectionHandle);

	MYSQL_ROW row;

	while ((row = mysql_fetch_row(result)))
		switch (type)
		{
			case PART_OF_SPEECH_WORDS_TABLE:
				output.push_back((void *) new SQLWord(row[0], row[1], row[2], row[3], row[4]));
				break;
			case PART_OF_SPEECH_ADJACENT_WORDS_TABLE:
				output.push_back((void *) new SQLAdjacentWord(row[0], row[1], row[2], row[3], row[4], row[5]));
				break;
			case PART_OF_SPEECH_FIRST_WORDS_TABLE:
				output.push_back((void *) new SQLFirstWord(row[0], row[1], row[2], row[3]));
				break;
			default:
				return output;
		}

	mysql_free_result(result);

	return output;
}

int PartOfSpeechTagger::PartOfSpeechConstant(string partOfSpeechString)
{
	string PARTS_OF_SPEECH[0x57] = { ".", "(", ")", "*", "--", ",", ":", "ABL", "ABN", "ABX", "AP", "AT", "BE", "BED", "BEDZ", "BEG", "BEM", "BEN", "BER", "BEZ", "CC", "CD", "CS", "DO", "DOD", "DOZ", "DT", "DTI", "DTS", "DTX", "EX", "FW", "HV", "HVD", "HVG", "HVN", "IN", "JJ", "JJR", "JJS", "JJT", "MD", "NC", "NN", "NN$", "NNS", "NNS$", "NP", "NP$", "NPS", "NPS$", "NR", "OD", "PN", "PN$", "PP$", "PP$$", "PPL", "PPLS", "PPO", "PPS", "PPSS", "PRP", "PRP$", "QL", "QLP", "RB", "RBR", "RBT", "RN", "RP", "TO", "UH", "VB", "VBD", "VBG", "VBN", "VBP", "VBZ", "WDT", "WP$", "WHO", "WPS", "WQL", "WRB", "``", "''" };

	for (int i = 0; i < 0x57; i++)
		if (ToUpperCase(partOfSpeechString) == PARTS_OF_SPEECH[i])
			return i;

	return -1;
}
string PartOfSpeechTagger::PartOfSpeech(string partOfSpeechAbbreviatedString)
{
	string PARTS_OF_SPEECH_FULL[0x57] = { "PERIOD", "LEFT_PARENTHESE", "RIGHT_PARENTHESE", "NOT", "DASH", "COMMA", "COLON", "PRE-QUALIFIER", "PRE-QUANTIFIER", "PRE-QUANTIFIER", "POST-DETERMINER", "ARTICLE", "BE", "WERE", "WAS", "BEING", "AM", "BEEN", "ARE", "IS", "COORDINATING_CONJUNCTION", "CARDINAL_NUMERAL", "SUBORDINATING_CONJUNCTION", "DO", "DID", "DOES", "SINGULAR_DETERMINER/QUANTIFIER", "SINGULAR/PLURAL_DETERMINER/QUANTIFIER", "PLURAL_DETERMINER", "DETERMINER/DOUBLE_CONJUNCTION", "EXISTENTIAL_THERE", "FOREIGN_WORD", "HAVE", "HAD", "HAVING", "HAD", "PREPOSITION", "ADJECTIVE", "COMPARATIVE_ADJECTIVE", "SEMANTICALLY_SUPERLATIVE_ADJECTIVE", "MORPHOLOGICALLY_SUPERLATIVE_ADJECTIVE", "MODAL_AUXILIARY", "CITED_WORD", "SINGULAR_NOUN", "POSSESSIVE_SINGULAR_NOUN", "PURAL_NOUN", "POSSESSIVE_PLURAL_NOUN", "PROPER_NOUN", "POSSESSIVE_PROPER_NOUN", "PLURAL_PROPER_NOUN", "POSSESSIVE_PLURAL_PROPER_NOUN", "ADVERBIAL_NOUN", "ORDINAL_NUMERAL", "NOMINAL_PRONOUN", "POSSESSIVE_NOMINAL_PRONOUN", "POSSESSIVE_PERSONAL_PRONOUN", "SECOND_NOMINAL_POSSESSIVE_PRONOUN", "SINGULAR_REFLEXIVE/INTENSIVE_PERSONAL_PRONOUN", "PLURAL_REFLEXIVE/INTENSIVE_PERSONAL_PRONOUN", "OBJECTIVE_PERSONAL_PRONOUN", "THIRD_SINGULAR_NOMINATIVE_PRONOUN", "OTHER_NOMINATIVE_PERSONAL_PRONOUN", "PERSONAL_PRONOUN", "POSSESSIVE_PRONOUN", "QUALIFIER", "POST_QUALIFIER", "ADVERB", "COMPARATIVE_ADVERB", "SUPERLATIVE_ADVERB", "NOMINAL_ADVERB", "ADVERB/PARTICLE", "INFINITIVE_MARKER_TO", "INTERJECTION", "VERB_BASE_FORM", "VERB_PAST_TENSE", "VERB_PRESENT_PARTICIPLE", "VERB_PAST_PARTICIPLE", "VERB_NON_THRID_PERSON_SINGULAR_PRESENT", "VERB_THIRD_SINGULAR_PRESENT", "WH_DETERMINER", "POSSESSIVE_WH_PRONOUN", "OBJECTIVE_WH_PRONOUN", "NOMINATIVE_WH_PRONOUN", "WH_QUALIFIER", "WH_ADVERB", "LEFT_QUOTE", "RIGHT_QUOTE" };

	int constant = this->PartOfSpeechConstant(partOfSpeechAbbreviatedString);

	if (constant != -1)
		return PARTS_OF_SPEECH_FULL[constant];
	else
		return "UNKNOWN";
}

#endif