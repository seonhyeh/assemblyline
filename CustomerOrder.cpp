// Seneca Student ID: 125635193
// Seneca email: shyeon@myseneca.ca
// Date of change : November 28, 2021
// MS2 output match However,
// MS3 output dosen't match due to I made somethig wrong.
// Date of completion: December 4, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"

using namespace std;
namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(string& str)
	{
		// 	extractToken(const std::string& str, size_t& next_pos, bool& more)
		Utilities utilities;
		size_t next_pos = 0;
		bool more = true;

		m_name = utilities.extractToken(str, next_pos, more);
		m_product = utilities.extractToken(str, next_pos, more);
		m_cntItem = count(str.begin(), str.end(), utilities.getDelimiter()) - 1;
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++)
		{
			m_lstItem[i] = new Item(utilities.extractToken(str, next_pos, more));
		}

		// After finishing extraction, this constructor updates CustomerOrder::m_widthField 
		// if the current value is smaller than the value stored in Utilities::m_widthField.
		if (utilities.getFieldWidth() > m_widthField)
		{
			m_widthField = utilities.getFieldWidth();
		}
	}

	// The copy constructor should throw an exception 
	// if called and the copy operator= should be deleted.
	CustomerOrder::CustomerOrder(const CustomerOrder& src)
	{
		throw "error";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
	{
		*this = move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
	{
		if (this != &src)
		{
			for (size_t i = 0; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;

			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_widthField = src.m_widthField;

			src.m_name = "";
			src.m_product = "";
			src.m_cntItem = 0;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		if (m_lstItem)
		{

			for (size_t i = 0; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_lstItem = nullptr;
		}
	}

	// returns true if all the items in the order have been filled; false otherwise
	bool CustomerOrder::isFilled() const 
	{
		bool filled = true;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (!m_lstItem[i]->m_isFilled)
			{
				filled = false;
			}
		}

		return filled;
	}

	//  returns true if all items specified by itemName have been filled. 
	// If the item doesn't exist in the order, this query returns true.
	bool CustomerOrder::isItemFilled(const string& itemName) const
	{
		bool filled = true;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_isFilled == false && m_lstItem[i]->m_itemName == itemName)
			{
				filled = false;
			}
		}

		return filled;
	}

	void CustomerOrder::fillItem(Station& station, ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; i++)
		{
			// if the order contains items handled
			if (m_lstItem[i]->m_itemName == station.getItemName())
			{
				// and the Station's inventory contains at least one item,
				if (station.getQuantity() > 0)
				{
					// subtracts 1 from the inventory
					station.updateQuantity();
					// updates Item::m_serialNumber and Item::m_isFilled. 
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					// It also prints the message Filled NAME, PRODUCT [ITEM_NAME].
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
				else
				{
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
			}
		}
	}

	/*SERIAL - a field of width 6
	ITEM_NAME - a field of size m_widthField
	STATUS is either FILLED or TO BE FILLED*/
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << right << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] "
				<< left << setw(m_widthField) << setfill(' ') << m_lstItem[i]->m_itemName
				<< " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
		}
	}
}