#ifndef STATION_H
#define STATION_H
#include<iostream>
#include<string>

namespace sdds {
	class Station {
		int s_id;
		std::string i_name;
		std::string s_dscp;
		size_t next_num;
		size_t curr_items;
		static size_t m_widthField ;
		static size_t id_generator ;
	public:
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // ! STATION_H
