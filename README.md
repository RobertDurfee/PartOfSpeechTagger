# PartOfSpeechTagger
C++ class for parsing English sentences with corresponding parts of speech.

### Initialization
```C++
PartOfSpeechTagger();
PartOfSpeechTagger(string server, string user, string password);
PartOfSpeechTagger(string brownCorpusDirectory, string server, string user, string password);
```
The `PartOfSpeechTagger` can be initialized three different ways:

 1. Without parameters, where the MYSQL connection is hardcoded.
 2. With the `server`, `user`, and `password` defined for a specific MYSQL connection.
 3. With an additional parameter specifying the location of the Brown Corpus resulting in an implicit call of the `InitializeDatabase` method.

### Parse to String
```C++
string ParseToString(string input, bool abbreviated = true);
```
This method takes an English sentence and returns the parts of speech of each word in the sentence as a string. If the user doesn't specify, the output will be abbreviated in the same manner as the Brown Corpus. If an unknown word is encountered, the output will be: "Unexpected SQL Query Result."

### Parse to Vector
```C++
vector<string> ParseToVector(string input, bool abbreviated = true);
```
This method takes an English sentence and returns the parts of speech of each word in the sentence as a vector of individual strings. If the user doesn't specify, the output will be abbreviated in the same manner as the Brown Corpus. If an unknown word is encountered, the output will be: "Unexpected SQL Query Result." in the first element.

### Initialize Database
```C++
void InitializeDatabase(string brownCorpusDirectory);
```
This method takes a really long time to run as it parses each file included in the Brown Corpus calculating corresponding probabilities of adjacency and tag assignment. It assumes that the server connection supplied in the constructor has a database called "LanguageData". This method also prints out status updates to the standard output stream.

### Deinitialization
```C++
~PartOfSpeechTagger();
```
This method simply closes the connection to the database that is opened in the constructor. No memory is allocated/deallocated in this class.

### First Word Structures
```C++
struct FirstWord
{
	FirstWord(string tag);

	string tag;
	int frequency;
};

struct SQLFirstWord
{
	SQLFirstWord(int ID, string PartOfSpeechString, int PartOfSpeechConstant, float Percentage);
	SQLFirstWord(string ID, string PartOfSpeechString, string PartOfSpeechConstant, string Percentage);

	int ID;
	string PartOfSpeechString;
	int PartOfSpeechConstant;
	float Percentage;
};
```
These structures hold the information about the first words of a sentence. The normal version simply contains the part of speech and the frequency in which it occurs in the Brown Corpus. The SQL version also contains an `ID` field supplied through a SQL query, converts the frequency to a percentage of overall occurences, and labels the part of speech by a string and a constant (defined in the `PartOfSpeechConstant` method).

Constructors are included to make initialization easier by also converting strings to the corresponding types.

### Words Structures
```C++
struct Word
{
	Word(string word, string tag);

	string word;
	string tag;
	int frequency;
};

struct SQLWord
{
	SQLWord(int ID, string Word, string PartOfSpeechString, int PartOfSpeechConstant, float Percentage);
	SQLWord(string ID, string Word, string PartOfSpeechString, string PartOfSpeechConstant, string Percentage);

	int ID;
	string Word;
	string PartOfSpeechString;
	int PartOfSpeechConstant;
	float Percentage;
};
```
These structures hold the information about the tag given to an individual word. The normal version simply contains the word, the part of speech, and the frequency in which it occurs in the Brown Corpus. The SQL version also contains an `ID` field supplied through a SQL query, converts frequency to a percentage of overall occurences, and labels the part of speech by a string and a constant (defined in the `PartOfSpeechConstant` method).

Constructors are included to make initialization easier by also converting strings to the corresponding types.

### Adjacent Words Structures
```C++
struct AdjacentWord
{
	AdjacentWord(string firstTag, string secondTag);

	string firsttag;
	string secondtag;
	int frequency;
};

struct SQLAdjacentWord
{
	SQLAdjacentWord(int ID, string FirstPartOfSpeechString, string SecondPartOfSpeechString, int FirstPartOfSpeechConstant, int SecondPartOfSpeechConstant, float Percentage);
	SQLAdjacentWord(string ID, string FirstPartOfSpeechString, string SecondPartOfSpeechString, string FirstPartOfSpeechConstant, string SecondPartOfSpeechConstant, string Percentage);

	int ID;
	string FirstPartOfSpeechString;
	string SecondPartOfSpeechString;
	int FirstPartOfSpeechConstant;
	int SecondPartOfSpeechConstant;
	float Percentage;
};
```
These structures hold the information about the tags given to two adjacent words. The normal version simply contains the first and second tag and the frequency in which the pair is encountered in the Brown Corpus. The SQL version also contains an `ID` field uspplied through a SQL query, converts the frequency to a percentage of overall occurences, and labels the parts of speech by strings and constants (defined in the `PartOfSpeechConstant` method).

Constructors are included to make initialization easier by also converting strings to the corresponding types.

### Example
```C++
#include "PartOfSpeechTagger.h"
#include <iostream>

using namespace std;

int main()
{
	PartOfSpeechTagger tagger;

	cout << tagger.ParseToString("Behind the door is a coat rack.", false);

	return 0;
}
```
Usage is pretty straightforward as the tagger is initialized using the hardcoded constructor and then a sentence is passed in as input. The resulting sequences of unabbreviated tags is then printed.
