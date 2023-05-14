#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include<iostream>
#include<iomanip>
#include"Utilities.h"
#include"Station.h"
#include"CustomerOrder.h"

namespace sdds {
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder:: CustomerOrder(const std::string& str) {
		Utilities tool;
		size_t next_pos = 0;
		bool more = true;
		m_name = tool.extractToken(str, next_pos, more);
		m_product = tool.extractToken(str, next_pos, more);
		while (more == true) {
			if (m_lstItem!= nullptr) {
				Item** tmp = new Item * [m_cntItem + 1]{nullptr}; // tmp as new array for Item*
				for (size_t i = 0; i < m_cntItem; i++) { // copy original data to tmp
					tmp[i] = m_lstItem[i];
				}
				if (m_lstItem != nullptr)
					delete[] m_lstItem;  // delete the original space
				std::string name = tool.extractToken(str, next_pos, more);
				tmp[m_cntItem] = new Item(name);  // add new item to last slot of tmp
				m_lstItem = tmp; // tmp as new local variable
				m_cntItem++;
			}
			else {
				m_lstItem = new Item * [1];
				std::string name = tool.extractToken(str, next_pos, more);
				m_lstItem[0] = new Item(name);
				m_cntItem++;
			}
		}
		m_widthField = (m_widthField < tool.getFieldWidth()) ? tool.getFieldWidth() : m_widthField;
	}
	
	CustomerOrder:: CustomerOrder(CustomerOrder&& R) noexcept {
		m_lstItem = nullptr;
		this->m_name = R.m_name;
		this->m_product = R.m_product;
		this->m_cntItem = R.m_cntItem;
		this->m_lstItem = R.m_lstItem;
		R.m_lstItem = nullptr;
		R.m_cntItem = 0;
	}
	CustomerOrder& CustomerOrder:: operator=(CustomerOrder&& R) noexcept {
		if (this != &R) {
			if (m_lstItem != nullptr) {
				for (size_t i = 0; i < m_cntItem; i++) {
					delete m_lstItem[i];
				}
				delete[] this->m_lstItem;
			}
			this->m_name = R.m_name;
			this->m_product = R.m_product;
			this->m_cntItem = R.m_cntItem;
			this->m_lstItem = R.m_lstItem;
			R.m_lstItem = nullptr;
			R.m_cntItem = 0;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const {
		bool allFilled = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_isFilled == false)
				allFilled = false;
		}
		return allFilled;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool isFilled = false;
		int exist = 0;
		bool rtr = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (itemName == m_lstItem[i]->m_itemName)
				exist++;
			if (m_lstItem[i]->m_isFilled == true)
				isFilled = true;
		}
		if (exist != 0)
			rtr= isFilled;
		if (exist == 0)
			rtr= true;
		return rtr;
	}
	bool CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool containAndUnfilled = false;
		bool rtr = true;
		int cnt = 0;
		size_t i;
		size_t mark;
		for (i = 0; i < m_cntItem; i++) {
			if (station.getItemName() == m_lstItem[i]->m_itemName && m_lstItem[i]->m_isFilled == false) {
				containAndUnfilled = true;
				mark = i;
				break;
			}
		}
		for (i = 0; i < m_cntItem; i++) {
			if (station.getItemName() == m_lstItem[i]->m_itemName && m_lstItem[i]->m_isFilled == false) {
				cnt++;
			}
		}
		if (containAndUnfilled == true) {
			if (station.getQuantity() > 0) {
				m_lstItem[mark]->m_serialNumber = station.getNextSerialNumber();
				m_lstItem[mark]->m_isFilled = true;
				station.updateQuantity();
				os << "    Filled " << this->m_name << ", " << this->m_product << " [" << m_lstItem[mark]->m_itemName << "]\n";
				rtr= true;
			}
			else {
				for(int i = 0; i<cnt; i++)
				os << "    Unable to fill " << this->m_name << ", " << this->m_product << " [" << m_lstItem[mark]->m_itemName << "]\n";
				rtr= false;
			}
		}
		return rtr;
	}
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name<<" - "<<m_product<<std::endl;
		size_t i = 0;
		for (i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6)<<std::right<<std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os <<std::setfill(' ') << std::left << std::setw(m_widthField) << m_lstItem[i]->m_itemName;
			if (m_lstItem[i]->m_isFilled == true)
				os << "   - FILLED\n";
			else {
				os << "   - TO BE FILLED\n";
			}
		}
	}
	bool CustomerOrder::hasItem(const std::string item) {
		size_t i;
		bool containAndUnfilled = false;
		for (i = 0; i < m_cntItem; i++) {
			if (item == m_lstItem[i]->m_itemName && m_lstItem[i]->m_isFilled == false) {
				containAndUnfilled = true;
				break;
			}
		}
		return containAndUnfilled;
	}
}