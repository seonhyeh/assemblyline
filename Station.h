// Name: Seonhye Hyeon
// Seneca Student ID: 125635193
// Seneca email: shyeon@myseneca.ca
// Date of completion: November 20, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <string>
#include "Utilities.h"

using namespace std;
namespace sdds
{
	class Station
	{
		// the id of the station (integer)
		int m_id = 0;
		// the name of the item handled by the station (string of characters)
		string m_name = "";
		// the description of the station (string of characters)
		string m_description = "";
		// the next serial number to be assigned to an item at this station (non-negative integer)
		unsigned m_serialNum = 0;
		// the number of items currently in stock (non-negative integer)
		unsigned m_quantity = 0;
		// Class Variables
		//  the maximum number of characters required to print to the screen the item name,
		// serial number and quantity for any object of type Station. Initial value is 0.
		static size_t m_widthField;
		//  a variable used to generate IDs for new instances of type Station
		static int id_generator;
	public:
		// custom 1 argument constructor
		Station(const string& record);
		const string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(ostream& os, bool full) const;
	};
}

#endif

