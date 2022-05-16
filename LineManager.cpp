// Name: Seonhye Hyeon
// Seneca Student ID: 125635193
// Seneca email: shyeon@myseneca.ca
// Date of completion: December 4, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <fstream>
#include <algorithm>
#include "LineManager.h"

using namespace std;
namespace sdds
{
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		ifstream in(file);  

		if (!in) 
		{
			throw "error";
		}

		Workstation* currentStation;
		Workstation* nextStation;
		Utilities utils;
		size_t next_pos = 0;
		string str = "";
		string current = "";
		string next = "";
		bool more = true;

		while (getline(in, str)) 
		{
			// This function stores the workstations in the order received from the file in the activeLine instance variable.
			// It loads the contents of the file, stores the address of the next workstation in each element of the collection,
			// extractToken(const std::string& str, size_t& next_pos, bool& more)
			current = utils.extractToken(str, next_pos, more);
			currentStation = *find_if(stations.begin(), stations.end(), [&](Workstation* cstation) 
				{ 
					return (cstation->getItemName() == current);
				});

			if (more) 
			{
				next = utils.extractToken(str, next_pos, more);
				nextStation = *find_if(stations.begin(), stations.end(), [&](Workstation* nstation) 
					{
						return (nstation->getItemName() == next);
					});
				currentStation->setNextStation(nextStation);
			}
			activeLine.push_back(currentStation);
		}

		//  identifies the first station in the assembly line and stores its address in the m_firstStation attribute. 
		m_firstStation = activeLine.front();
		// updates the attribute that holds the total number of orders in the pending queue
		m_cntCustomerOrder = pending.size();
	}

	void LineManager::linkStations()
	{
		// stores the reordered collection in the same instance variable.
		vector<Workstation*> station;
		// The elements in the reordered collection start with the first station, 
		Workstation* nstation = m_firstStation;

		// proceeds to the next, and so forth until the end of the line.
		do 
		{
			station.push_back(nstation);
			nstation = nstation->getNextStation();

		} while (nstation);

		activeLine = station;
	}

	bool LineManager::run(ostream& os)
	{
		// keeps track of the current iteration number (use a local variable)
		static size_t count = 1;

		// in the format Line Manager Iteration: COUNT<endl>
		os << "Line Manager Iteration: " << count++ << endl;

		// if the pending queue has a CustomerOrder object,
		if (!pending.empty())
		{
			//  moves the order at the front of the queue to the m_firstStation of the activeLine
		    *activeLine.front() += move(pending.front());
			//  remove it from the queue
			pending.pop_front();
		}

		// for each station on the line, executes one fill operation
		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* station) 
		{
			station->fill(os);
		});

		// for each station on the line, attempts to move a CustomerOrder down the line
		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* station) 
		{
			station->attemptToMoveOrder(); 
		});

		// return true if all customer orders (m_cntCustomerOrder) have been filled, otherwise returns false.
		return m_cntCustomerOrder == completed.size() + incomplete.size();
	}

	void LineManager::display(ostream& os) const
	{
		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* station) 
		{
			station->display(os);
		});
	}
}