#ifndef STATION_H
#define STATION_H
#include<iostream>
#include<string>

namespace sdds {
	class Station {
		int s_id; // id for the station
		std::string i_name; // the name for the item it produced
		std::string s_dscp; // station description
		size_t next_num; // the next serial number
		size_t curr_items; // the current number of items
		static size_t m_widthField ;
		static size_t id_generator ; // a static id generator for all stations
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
