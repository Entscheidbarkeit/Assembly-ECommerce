#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H
#include<string>
#include<iomanip>
#include"Utilities.h"
#include"Station.h"
namespace sdds {
	// the struction for the Items in the Order and Station
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };  // default initialize the serialNumber with 0
		bool m_isFilled{ false };  // default initialize the isFilled with false

		Item(const std::string& src) : m_itemName(src) {}; // initialize the item name with parameter
	};
	// the CustomerOrder class
	class CustomerOrder {
	private :
		std::string m_name; // the name of customer
		std::string m_product; // the name of this order
		size_t m_cntItem =0;  // counts of contained Item
		Item** m_lstItem = nullptr; // the list of items contained in the order
		static size_t m_widthField; // the minimal length for printing
	public:
		CustomerOrder();
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder&) {
			throw;
		};
		CustomerOrder& operator=(const CustomerOrder&) = delete;  // no copy constructor
		CustomerOrder(CustomerOrder&& R) noexcept;  // move constructor
		CustomerOrder& operator=(CustomerOrder&& R) noexcept;  // operator overload for move constructor
		~CustomerOrder();  // destructor
		bool isOrderFilled() const;  // examin if this order is filled
		bool isItemFilled(const std::string& itemName) const; // examin if the items in the order are filled
		bool fillItem(Station& station, std::ostream& os);  // fill the Item
		void display(std::ostream& os) const; // the String display for the order
		bool hasItem(const std::string item);  // examin if the order has a specified item
	};
}
#endif // !CUSTOMERORDER_H
