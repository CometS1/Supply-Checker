#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "OrderManager.h"

void OrderManager::push_back(CustomerOrder&& customerOrder){
        customerOrders.push_back(std::move(customerOrder));
}


     
void OrderManager::pop(){
 customerOrders.pop_back();
}
     
bool OrderManager::empty() const{
 return customerOrders.empty();
}

std::vector<CustomerOrder>::iterator OrderManager::begin(){
 return customerOrders.begin();
 
}

std::vector<CustomerOrder>::iterator OrderManager::end(){
 return customerOrders.end();
 
}

const std::vector<CustomerOrder>::const_iterator OrderManager::cbegin() const{
 return customerOrders.begin();
 
}

const std::vector<CustomerOrder>::const_iterator OrderManager::cend() const{
 return customerOrders.end();
 
}

void OrderManager::display(std::ostream& os) const{
 for (const CustomerOrder& customerOrder : customerOrders)
         customerOrder.display(os);
}

void validate(const OrderManager& orderMan, const ItemManager& itemMan, std::ostream& os){

        for (auto orderIt = orderMan.cbegin(); orderIt != orderMan.cend(); orderIt++) {
                for (unsigned int i = 0; i < orderIt->noOrders(); i++) {
                        std::vector<Item>::const_iterator it = std::find_if
                                (itemMan.cbegin(), itemMan.cend(), 
                                [&] (Item item) { return item.getName() == (*orderIt)[i];} );

                        if (it == itemMan.cend())
                                os << (*orderIt)[i] << " is unavailable\n";

                        }
                }
}