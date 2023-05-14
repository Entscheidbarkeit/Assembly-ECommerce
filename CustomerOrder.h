#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H
#include<string>
#include<iomanip>
#include"Utilities.h"
#include"Station.h"
namespace sdds {
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};
	class CustomerOrder {
	private :
		std::string m_name;
		std::string m_product;
		size_t m_cntItem =0;
		Item** m_lstItem = nullptr;
		static size_t m_widthField;
	public:
		CustomerOrder();
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder&) {
			throw;
		};
		CustomerOrder& operator=(const CustomerOrder&) = delete;
		CustomerOrder(CustomerOrder&& R) noexcept;
		CustomerOrder& operator=(CustomerOrder&& R) noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		bool fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
		bool hasItem(const std::string item);
	};
}
#endif // !CUSTOMERORDER_H
