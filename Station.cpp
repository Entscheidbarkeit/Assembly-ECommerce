#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<iomanip>
#include"Utilities.h"
#include"Station.h"

namespace sdds{
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;
	Station:: Station(const std::string& str) {
		bool more = true;
		size_t next_pos = 0;
		Utilities tool;
		i_name = tool.extractToken(str, next_pos, more);
		next_num = (size_t)std::stoi(tool.extractToken(str, next_pos, more).c_str());
		curr_items = (size_t)std::stoi(tool.extractToken(str, next_pos, more).c_str());
		m_widthField = std::max(m_widthField, tool.getFieldWidth());
		s_dscp = tool.extractToken(str, next_pos, more);
		id_generator++;
		this->s_id = id_generator;
	}
	const std::string& Station::getItemName() const {
		return i_name;
	}
	size_t Station::getNextSerialNumber() {
		next_num++;
		return next_num-1;
	}
	size_t Station::getQuantity() const {
		return this->curr_items;
	}
	void Station:: updateQuantity() {
		if (this->curr_items > 0) {
			curr_items--;
		}
	}
	void Station:: display(std::ostream& os, bool full) const {
		if (full == false) {
			os << std::setw(3) << std::right << std::setfill('0') << this->s_id << " | ";
			os << std::setw(m_widthField)<< std::setfill(' ') << std::left << this->i_name << "  | ";
			os << std::setw(6) << std::setfill('0') << std::right << this->next_num << " | "<<std::endl;
		}
		else {
			os << std::setw(3) << std::right << std::setfill('0') << this->s_id << " | ";
			os << std::setw(m_widthField) << std::setfill(' ') << std::left << this->i_name << "  | ";
			os << std::setw(6) << std::setfill('0') << std::right << this->next_num << " | ";
			os << std::setw(4) <<  std::setfill(' ')<< std::right << this->curr_items << " | ";
			os << this->s_dscp << std::endl;
		}
	}
}