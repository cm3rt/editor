//parse the XML files
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using std::cout;
using std::endl;
using std::ifstream;

class Parser
{
public:
	Parser();
	void get_variables();

private:
	const int MAX_CHARS_PER_LINE;
	const int MAX_TOKENS_PER_LINE;
	const char* const DELIMITER;
	int line;
	std::string varName;
}; 

Parser::Parser() : 
	DELIMITER(" "),
	varName(),
	MAX_CHARS_PER_LINE(520),
	MAX_TOKENS_PER_LINE(20)
{
  // create a file-reading object
  ifstream fin;
  fin.open("info.txt"); // open a file
  if (!fin.good()) 
    cout << "Failure"; // exit if file not found
  
  // read each line of the file
  while (!fin.eof())
  {
    // read an entire line into memory
    char buf[512];
    fin.getline(buf, 512);
    
    // parse the line into blank-delimited tokens
    int n = 0; // a for-loop index
    
    // array to store memory addresses of the tokens in buf
    const char* token[20] = {}; // initialize to 0
    
    // parse the line
    token[0] = strtok(buf, DELIMITER); // first token
    if (token[0]) // zero if line is blank
    {
		varName = token[0];
      for (n = 1; n < 20; n++)
      {
        token[n] = strtok(0, DELIMITER); // subsequent tokens
        if (!token[n]) break; // no more tokens
      }
    }

    // process (print) the tokens
    for (int i = 0; i < n; i++) // n = #of tokens
      cout << "Token[" << i << "] = " << token[i] << endl;
    cout << endl;
  }
}