// Name: Seonhye Hyeon
// Seneca Student ID: 125635193
// Seneca email: shyeon@myseneca.ca
// Date of completion: November 20, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

using namespace std;
namespace sdds
{
	char Utilities::m_delimiter = ' ';

	// sets the field width of the current object to the value of parameter newWidth
	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	// returns the field width of the current object
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	// extracts a token from string str referred to by the first parameter
	string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		size_t fpos = next_pos;
		string  extractedToken = "";

		next_pos = str.find(m_delimiter, fpos);

		// If successful, this function returns a copy of the extracted token found, 
		// updates next_pos with the position of the next token, and sets more to true (false otherwise).

		if (next_pos == string::npos) // cannot find next_pos
		{
			extractedToken = str.substr(fpos);

			// This function updates the current object's m_widthField data member 
			// if its current value is less than the size of the token extracted.
			if (extractedToken.length() > getFieldWidth())
			{
				setFieldWidth(extractedToken.length());
			}

			more = false;
		}
		// This function reports an exception if a delimiter is found at next_pos.
		else if (fpos == next_pos)
		{
			more = false;
			throw "error";
		}
		else
		{
			extractedToken = str.substr(fpos, next_pos - fpos);
			if (extractedToken.length() > getFieldWidth())
			{
				setFieldWidth(extractedToken.length());
			}
			more = true;
		}

		next_pos++;
		return extractedToken;
	}

	// sets the delimiter for this class to the character received
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	//  returns the delimiter for this class.
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}