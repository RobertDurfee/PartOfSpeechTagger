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
	FirstWord(string);
	void IncreaseFrequency();

	string tag;
	int frequency;
};

struct SQLFirstWord
{
	SQLFirstWord(int, string, int, float);
	SQLFirstWord(string, string, string, string);

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
	Word(string, string);
	void IncreaseFrequency();

	string word;
	string tag;
	int frequency;
};

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
```

### Adjacent Words Structures
```C++
struct AdjacentWord
{
	AdjacentWord(string, string);
	void IncreaseFrequency();

	string firsttag;
	string secondtag;
	int frequency;
};

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
```

### Example
```C++
```
