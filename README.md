# PartOfSpeechTagger
C++ class for parsing English sentences with corresponding parts of speech.

### Initialization
```C++
PartOfSpeechTagger();
PartOfSpeechTagger(string server, string user, string password);
PartOfSpeechTagger(string brownCorpusDirectory, string server, string user, string password);
```

### Parse to String
```C++
string ParseToString(string input, bool abbreviated);
```

### Parse to Vector
```C++
vector<string> ParseToVector(string input, bool abbreviated);
```

### Initialize Database
```C++
void InitializeDatabase(string brownCorpusDirectory);
```

### Deinitialization
```C++
~PartOfSpeechTagger();
```

### First Word Structures
```C++
struct FirstWord
{
	FirstWord(string tag);
	void IncreaseFrequency();

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

### Words Structures
```C++
struct Word
{
	Word(string word, string tag);
	void IncreaseFrequency();

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

### Adjacent Words Structures
```C++
struct AdjacentWord
{
	AdjacentWord(string firstTag, string secondTag);
	void IncreaseFrequency();

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
