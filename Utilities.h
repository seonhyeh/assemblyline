// Name: Seonhye Hyeon
// Seneca Student ID: 125635193
// Seneca email: shyeon@myseneca.ca
// Date of completion: November 20, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>
#include <string>

using namespace std;
namespace sdds
{
	class Utilities
	{
		// specifies the length of the token extracted; used for display purposes; default value is 1
		size_t m_widthField = 1;
		// class variable
		//  separates the tokens in any given std::string object.
		static char m_delimiter;
	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		string extractToken(const string& str, size_t& next_pos, bool& more);
		// Class Functions
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};

}
#endif