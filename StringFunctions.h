#ifndef STRING_FUNCTIONS_HEADER
#define STRING_FUNCTIONS_HEADER

#include <sstream>  //stringstream
#include <string>   //string
#include <vector>   //vector
#include <stdarg.h> //va_list, va_start, va_arg, va_end

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
	while ((index = (int)input.find("%s", ++index)) != -1)
		count++;

	va_list List;
	va_start(List, input);

	for (int i = 0; i < count; i++)
	{
		input = input.erase((result = (int)input.find("%s")), 2);
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

#endif