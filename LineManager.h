#ifndef LINEMANAGER_H
#define LINEMANAGER_H
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>
#include"CustomerOrder.h"
#include"Workstation.h"

namespace sdds {
	class LineManager {
		std::vector<Workstation*> m_activeLine;
		size_t m_cntCustomerOrder = 0;
		Workstation* m_firstStation;
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif // !LINE_MANAGER_H

