// Name: Seonhye Hyeon
// Seneca Student ID: 125635193
// Seneca email: shyeon@myseneca.ca
// Date of completion: November 27, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include <string>
#include "Station.h"

using namespace std;
namespace sdds
{
	struct Item
	{
		string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const string& src) : m_itemName(src) {};
	};

	class CustomerOrder
	{
		string m_name = "";
		string m_product = "";
		size_t m_cntItem = 0;
		//  Each element of the array points to a dynamically allocated object of type Item
		Item** m_lstItem = nullptr;
		// Class Variable
		static size_t m_widthField;
	public:
		// default constructor
		CustomerOrder() {};
		// a custom 1-arg constructor that takes a reference to an unmodifiable string.
		CustomerOrder(string& str);
		// a CustomerOrder object should not allow copy operations
		CustomerOrder(const CustomerOrder&);
		CustomerOrder& operator=(const CustomerOrder&) = delete;
		// move semantics
		CustomerOrder(CustomerOrder&&) noexcept;
		CustomerOrder& operator=(CustomerOrder&&) noexcept;
		// a destructor
		~CustomerOrder();
		bool isFilled() const;
		bool isItemFilled(const string& itemName) const;
		void fillItem(Station& station, ostream& os);
		void display(ostream& os) const;
	};
}

#endif