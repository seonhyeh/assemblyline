// Name: Seonhye Hyeon
// Seneca Student ID: 125635193
// Seneca email: shyeon@myseneca.ca
// Date of completion: November 20, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include <algorithm>
#include "Station.h"

using namespace std;
namespace sdds
{
	size_t Station::m_widthField = 0;
	int Station::id_generator = 1;

	Station::Station(const string& record)
	{
		Utilities utilities;
		bool more = true;
		size_t npos = 0;

		// Bed,123456,5,Queen size bed with headboard
		m_name = utilities.extractToken(record, npos, more);
		m_serialNum = stoi(utilities.extractToken(record, npos, more));
		m_quantity = stoi(utilities.extractToken(record, npos, more));
		// before extracting description, it updates Station::m_widthField to the maximum value of
		// Station::m_widthField and Utilities::m_widthField.
		m_widthField = max(m_widthField, utilities.getFieldWidth());
		m_description = utilities.extractToken(record, npos, more);

		// increade Id number.
		m_id = id_generator++;
	}

	// returns the name of the current Station object
	const string& Station::getItemName() const
	{
		return m_name;
	}

	// returns the next serial number to be used on the assembly line and increments m_serialNumber
	size_t Station::getNextSerialNumber()
	{
		return m_serialNum++;
	}

	//  returns the remaining quantity of items in the Station object
	size_t Station::getQuantity() const
	{
		return m_quantity;
	}

	//  subtracts 1 from the available quantity; should not drop below 0
	void Station::updateQuantity()
	{
		if (m_quantity > 0)
		{
			m_quantity--;
		}
	}

	void Station::display(ostream& os, bool full) const
	{

		//  inserts only the ID, name, and serial number in the format: [ID] Item: NAME [SERIAL]
		os << "[" << right << setw(3) << setfill('0') << m_id << "] Item: "
			<< left << setw(m_widthField) << setfill(' ') << m_name
			<< " [" << right << setw(6) << setfill('0') << m_serialNum << "]";

		if (full)
		{
			// [ID] Item NAME [SERIAL] Quantity: QTY Description: DESCRIPTION
			os << " Quantity: " << left << setw(m_widthField) << setfill(' ') << m_quantity <<
				" Description: " << m_description;
		}
		os << endl;
	}
}