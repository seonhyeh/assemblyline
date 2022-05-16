// Name: Seonhye Hyeon
// Seneca Student ID: 125635193
// Seneca email: shyeon@myseneca.ca
// Date of completion: December 4, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <string>
#include <deque> //non-contiquous storage of variable size, double-ended queue(OOP345)
#include "CustomerOrder.h"

using namespace std;
namespace sdds
{
	// three double - ended queues of CustomerOrder (global variables)
	// orders to be placed onto the assembly line at the first station.
	extern deque<CustomerOrder> pending;
	// orders that have been removed from the last station and have been completely filled.
	extern deque<CustomerOrder> completed;
	// orders that have been removed from the last station and could not be filled completely.
	extern deque<CustomerOrder> incomplete;

	// Each Workstation is-a-kind-of Station
	class Workstation : public Station
	{
		deque<CustomerOrder>m_orders;
		Workstation* m_pNextStation = nullptr;
	public:
		// a custom 1-arg constructor 
		Workstation(string& str);
		void fill(ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station=nullptr);
		Workstation* getNextStation() const;
		void display(ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}

#endif