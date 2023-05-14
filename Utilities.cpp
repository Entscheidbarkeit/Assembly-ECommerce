#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<iomanip>
#include"Utilities.h"

namespace sdds {
	char Utilities::m_delimiter = '0';
	size_t Utilities::m_widthField = 0;
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		if (str[next_pos] == m_delimiter) {
			more = false;
			throw "err";
		}
		else {
			std::string rtr;
			size_t i = next_pos;
			if (next_pos == 0) {
				setFieldWidth(0);
			}
			while (str[i] != m_delimiter && i < str.length()) {
				if (str[i] != ' ') {
					rtr += str[i];
				}
				else {
					if (i > 0 && i < str.length()) {
						if (str[i - 1] != ' ' && str[i + 1] != ' ' && str[i + 1] != m_delimiter && str[i - 1] != m_delimiter)
							rtr += str[i];
					}
				}
				i++;
			}
			if (i == str.length()) {
				more = false;
			}
			if (str[i] == m_delimiter) {
				more = true;
				next_pos = i + 1;
			}
			if (m_widthField < rtr.length())
				setFieldWidth(rtr.length());
			return rtr;
		}
	}
	
}