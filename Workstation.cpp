#define _CRT_SECURE_NO_WARNINGS
#include <deque>
#include <string>
#include "CustomerOrder.h"
#include "Workstation.h"

namespace sdds {
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;
	// try to fill the order and set the fillTried to true. updates the cannotBeFilled
	void Workstation:: fill(std::ostream& os) {
		if (nowO < m_orders.size()) {
			cannotBeFilled = m_orders[nowO].fillItem(*this, os);
			fillTried = true;
		}
	}
	bool Workstation::attemptToMoveOrder() {
		if (nowO < m_orders.size()) {
			// if the current station is unable to fill the order then move
			if (m_orders[nowO].hasItem(this->getItemName()) == false || this->getQuantity() == 0) {
				if (m_pNextStation != nullptr) {
					m_pNextStation->m_orders.emplace_back(std::move(m_orders[nowO]));
					nowO++;
					return true;
				}
				else {// if the current order is filled and doesn't contain the item then move
					if (m_orders[nowO].hasItem(this->getItemName()) == false && m_orders[nowO].isOrderFilled() == true) {
						g_completed.emplace_back(std::move(m_orders[nowO]));
						nowO++;
						return true;
					}
					// if the current order is not filled then move
					if (m_orders[nowO].isOrderFilled() == false) {
						g_incomplete.emplace_back(std::move(m_orders[nowO]));
						nowO++;
						return true;
					}
				}
			}
		}
		// other cases return false
		else
			return false;
		return false;
	}
	// point to the next station
	void Workstation::setNextStation(Workstation* station) {
		m_pNextStation = station;
	}
	// get the next station
	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}
	// diplay the assembly line
	void Workstation::display(std::ostream& os) const {
		if (m_pNextStation == nullptr)
			os << this->getItemName() << " --> End of Line" << std::endl;
		else {
			os << this->getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
		}
	}
	// add orders to current order list
	Workstation& Workstation:: operator+=(CustomerOrder&& newOrder) {
		m_orders.emplace_back(std::move(newOrder));
		return*this;
	}
}