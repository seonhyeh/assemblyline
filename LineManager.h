// Name: Seonhye Hyeon
// Seneca Student ID: 125635193
// Seneca email: shyeon@myseneca.ca
// Date of completion: December 4, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include "Workstation.h"

using namespace std;
namespace sdds
{
	class LineManager
	{
		// the collection of workstations for the current assembly line.
		vector<Workstation*> activeLine;
		// the total number of CustomerOrder objects
		size_t m_cntCustomerOrder = 0;
		// points to the first active station on the current line
		Workstation* m_firstStation = nullptr;
	public:
		LineManager(const string& file, const vector<Workstation*>& stations);
		void linkStations(); 
		bool run(ostream& os);
		void display(ostream& os) const;
	};
}

#endif

