#ifndef WORKSTATION_H
#define WORKSTATION_H
#include <deque>
#include <string>
#include "CustomerOrder.h"
namespace sdds {
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;
	class Workstation : public Station{
		std::deque<CustomerOrder> m_orders;
		size_t nowO = 0;
		Workstation* m_pNextStation = nullptr;
		bool fillTried = false;
		bool cannotBeFilled = false;
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

