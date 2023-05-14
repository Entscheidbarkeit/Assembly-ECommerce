#ifndef WORKSTATION_H
#define WORKSTATION_H
#include <deque>
#include <string>
#include "CustomerOrder.h"
namespace sdds {
	extern std::deque<CustomerOrder> g_pending; // the deque stores the orders to be processed
	extern std::deque<CustomerOrder> g_completed; // the deque stores the completed orders
	extern std::deque<CustomerOrder> g_incomplete; // the deque stores the incomplete orders
	// Wordstation extends the Station class
	class Workstation : public Station{
		std::deque<CustomerOrder> m_orders; //the orders in the station
		size_t nowO = 0;  // current orders in the station
		Workstation* m_pNextStation = nullptr; // the next station
		bool fillTried = false; // if the current order is tried to be filled
		bool cannotBeFilled = false; // if the curren order is unable to be filled
	public:
		Workstation(const Workstation& r) = delete;
		Workstation(Workstation&& r) = delete;
		Workstation(const std::string& str) : Station(str) {};
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}
#endif // !WORKSTATION_H

