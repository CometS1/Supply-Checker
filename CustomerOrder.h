#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>


  class Item;
  class ItemOrder;

  class CustomerOrder {
  private:
    std::string   name;
    std::string   product;
    unsigned int  nOrders;
    static char   delimiter;
    static size_t fieldWidth;
    std::vector<std::shared_ptr <ItemOrder>> _order;

  public:

    CustomerOrder (const std::string& record);
    CustomerOrder (const CustomerOrder& source);
    CustomerOrder& operator=(const CustomerOrder&);
    CustomerOrder (CustomerOrder&&);
    CustomerOrder&& operator=(CustomerOrder&&);
    ~CustomerOrder ();
    unsigned int noOrders () const;
    const std::string& operator [] (unsigned int i) const;
    void fill (Item& i);
    void remove (Item& i);
    bool empty () const;
    void display (std::ostream&) const;
    static void setDelimiter (const char d) {
      delimiter = d;
    }
  };