#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>
#include"CustomerOrder.h"
#include"Workstation.h"
#include"LineManager.h"

namespace sdds {
	// the constructor reads from the AssemblyLine.txt(or other data alike) 
	// and organize the assembly line with the information provided through pointers
	// the second parameters contains all the station available
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		std::fstream File(file);
		if (!File)
			throw;
		else {
			while (File.peek() != EOF) {
				Workstation* tmpp;
				std::string tmp; // the string of a line
				std::string l, r; // the name of stations, if the information are seperated with '|'
				getline(File, tmp); // read a line from file and store into line
				size_t pos = 0;
				pos = tmp.find('|');// the posotion of '|'
				if (pos != std::string::npos) {
					l = tmp.substr(0, pos); // l for the left string to '|'
					r = tmp.substr(pos + 1); // r for the right
					std::vector<Workstation*>::const_iterator first = std::find_if(stations.begin(), stations.end(), [&](Workstation* i) {
						bool rtr = false;
					if (i->getItemName() == l) {
						rtr = true;
					}
					return rtr;
						});
					tmpp = *first;
					std::vector<Workstation*>::const_iterator second = std::find_if(stations.begin(), stations.end(), [&](Workstation* i) {
						bool rtr = false;
					if (i->getItemName() == r) {
						rtr = true;
					}
						return rtr;
						});
					tmpp->setNextStation(*second); //point to the next station
					m_activeLine.push_back(tmpp); // push bach the updated station
					m_cntCustomerOrder++;
				}
				else { // if the string do not contain '|'
					std::vector<Workstation*>::const_iterator first = std::find_if(stations.begin(), stations.end(), [&](Workstation* i) {
						bool rtr =false;
					if (i->getItemName() == tmp) {
						rtr = true;
					}
						return rtr;
						});
					tmpp = *first;
					m_activeLine.push_back(tmpp);
					m_cntCustomerOrder++;
				}
			}
		}
		// iterate the whole assembly line and determin the beginning station 
		// by determin which of the station is not referred
		Workstation* tmpp;
		std::vector<Workstation*>::iterator begin1 = m_activeLine.begin();
		std::vector<Workstation*>::const_iterator firstE;
		std::for_each(begin1, m_activeLine.end(), [&](Workstation* i) { 
			bool isReferred = false;
			std::vector<Workstation*>::iterator begin2 = m_activeLine.begin();
				for_each(begin2, m_activeLine.end(), [&](Workstation* j) {
					if (j->getNextStation() == i)
					isReferred = true;
				});
			if (isReferred == false)
				tmpp = i;
		});
		m_firstStation = tmpp;
	}
	//  sort the stations in the active line with a correct order
	void LineManager::reorderStations() {
		// set a temporary vector for sorted station
		std::vector<Workstation*> sorted;
		for (size_t i = 0; i < m_cntCustomerOrder - 1; i++) {
			// push the first station in the empty vector
			if (sorted.empty())
			{
				sorted.push_back(m_firstStation);
			}
			Workstation* curr = sorted[sorted.size() - 1]; // store the current station
			Workstation* tmpp;  // store the station that is next to current station
			std::vector<Workstation*>::const_iterator found = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* i) {
				bool rtr = false;
				if (curr->getNextStation()->getItemName() == i->getItemName()) {
					rtr = true;
				}
				return rtr;
			});
			tmpp = *found;
			sorted.push_back(tmpp);
		}
		m_activeLine.clear();
		// push the sorted stations back to active line
		for (size_t i = 0; i < m_cntCustomerOrder; i++) {
			m_activeLine.push_back(sorted[i]);
		}
	}
	// run the assembly line
	bool LineManager::run(std::ostream& os) {
		static size_t cnt = 1;//process all the orders that are pending
		if (cnt <= g_pending.size())
			*m_firstStation += std::move(g_pending[cnt - 1]);
		os << "Line Manager Iteration: " << cnt << std::endl;
		// each station on the assembly line fills and move oder to the next station
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* j) {
			j->fill(os);
			});
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* j) {
			j->attemptToMoveOrder();
			});
		cnt++;
		if (g_completed.size() + g_incomplete.size() == g_pending.size()) // if all the order are processed then return true
			return true;
		else
			return false;
	}
	// show the status in each station
	void LineManager::display(std::ostream& os) const {
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* i) {
			i->display(os);
			});
	}
}