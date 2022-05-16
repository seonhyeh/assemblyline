// Name: Seonhye Hyeon
// Seneca Student ID: 125635193
// Seneca email: shyeon@myseneca.ca
// Date of completion: December 4, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

using namespace std;
namespace sdds
{
    deque<CustomerOrder> pending;
    deque<CustomerOrder> completed;
    deque<CustomerOrder> incomplete;

    // receives a reference to an unmodifiable reference to std::string 
    // and passes it to the Station base class.
    Workstation::Workstation(string& str) :Station(str) {}

    // this modifier fills the order at the front of the queue, 
    // if there are CustomerOrders in the queue; otherwise, does nothing.
    void Workstation::fill(ostream& os)
    {
        if (!m_orders.empty())
        {
            m_orders.front().fillItem(*this, os);
        }
    }

    // attempts to move the order order at the front of the queue to the next station in the assembly line
    bool Workstation::attemptToMoveOrder()
    {
        bool moved = false;

        if (!m_orders.empty()) 
        {
            // if the order requires no more service at this station, move it to the next station
            // if the order cannot be filled (not enough inventory), move the order to the next station
            if (getQuantity() == 0 || m_orders.front().isItemFilled(getItemName()))
            {
                if (m_pNextStation)
                {
                    *m_pNextStation += move(m_orders.front());
                }
                // if there is no next station in the assembly line, then the order is moved into completed queue
                else if (m_orders.front().isFilled())
                {
                    completed.push_back(move(m_orders.front()));
                }
                // if there is no next station in the assembly line, then the order is moved into incomplete queue.
                else
                {
                    incomplete.push_back(move(m_orders.front()));
                }
                m_orders.pop_front();

                moved = true;
            }
        }

        return moved;
    }

    //  this modifier stores the address of the referenced Workstation object in the pointer to the m_pNextStation.
    // Parameter defaults to nullptr.
    void Workstation::setNextStation(Workstation* station)
    {
        m_pNextStation = station;
    }

    // this query returns the address of next Workstation
    Workstation* Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os) const
    {
        // ITEM_NAME --> NEXT_ITEM_NAME
        // if the current object is the last Workstation (m_pNextWorkstation is nullptr)
        if (!m_pNextStation)
        {
            os << getItemName() << " --> " << "End of Line" << endl;
        }
        else
        {
            os << getItemName() << " --> " << m_pNextStation->getItemName() << endl;
        }
    }


    // moves the CustomerOrder referenced in parameter newOrder to the back of the queue.
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
    {
        m_orders.push_back(move(newOrder));
        return *this;
    }
}