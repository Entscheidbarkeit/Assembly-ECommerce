#ifndef UTILITIES_H
#define UTILITIES_H
#include<Cstring>

namespace sdds {
	class Utilities {
		static size_t m_widthField; // the minimal space for string
		static char m_delimiter; // the delimiter in the txt file
	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter) {
			m_delimiter = newDelimiter;
		}
		static char getDelimiter() {
			return m_delimiter;
		}
	};
}
#endif // !UTILITIES_H
