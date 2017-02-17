#include "PartOfSpeechTagger.h"

int main()
{
	PartOfSpeechTagger tagger;

	cout << tagger.ParseToString("behind the door is a coat rack.", false);

	return 0;
}