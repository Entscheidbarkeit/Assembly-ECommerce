#define _CRT_SECURE_NO_WARNINGS
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>
#include"CustomerOrder.h"
#include"Workstation.h"
#include"LineManager.h"

namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		std::fstream File(file);
		if (!File)
			throw;
		else {
			while (File.peek() != EOF) {
				Workstation* tmpp;
				std::string tmp;
				std::string l, r;
				getline(File, tmp);
				size_t pos = 0;
				pos = tmp.find('|');
				if (pos != std::string::npos) {
					l = tmp.substr(0, pos);
					r = tmp.substr(pos + 1);
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
					tmpp->setNextStation(*second); //if there is no such stations it will be an exception
					m_activeLine.push_back(tmpp);
					m_cntCustomerOrder++;
				}
				else {
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
		Workstation* tmpp;
		std::vector<Workstation*>::iterator begin1 = m_activeLine.begin();
		std::vector<Workstation*>::const_iterator firstE;
		std::for_each(begin1, m_activeLine.end(), [&](Workstation* i) { //find_if doesn't work???
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
	void LineManager::reorderStations() {
		std::vector<Workstation*> sorted;
		for (size_t i = 0; i < m_cntCustomerOrder - 1; i++) {
			if (sorted.empty())
			{
				sorted.push_back(m_firstStation);
			}
			Workstation* curr = sorted[sorted.size() - 1];
			Workstation* tmpp;
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
		for (size_t i = 0; i < m_cntCustomerOrder; i++) {
			m_activeLine.push_back(sorted[i]);
		}
	}
	bool LineManager::run(std::ostream& os) {
		static size_t cnt = 1;
		if (cnt <= g_pending.size())
			*m_firstStation += std::move(g_pending[cnt - 1]);
		os << "Line Manager Iteration: " << cnt << std::endl;
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* j) {
			j->fill(os);
			});
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* j) {
			j->attemptToMoveOrder();
			});
		cnt++;
		if (g_completed.size() + g_incomplete.size() == g_pending.size())
			return true;
		else
			return false;
	}
	void LineManager::display(std::ostream& os) const {
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* i) {
			i->display(os);
			});
	}
}