#ifndef LINEMANAGER_H
#define LINEMANAGER_H
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>
#include"CustomerOrder.h"
#include"Workstation.h"

namespace sdds {
	// the line manager manages all the stations on the assembly line
	class LineManager {
		std::vector<Workstation*> m_activeLine; // the actual assembly line with stations
		size_t m_cntCustomerOrder = 0;  // the recieved customer orders
		Workstation* m_firstStation;  // the pointer for the first station
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif // !LINE_MANAGER_H

