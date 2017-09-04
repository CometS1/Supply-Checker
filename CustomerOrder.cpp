#include <iomanip>
#include "CustomerOrder.h"
#include "ItemOrder.h"
#include "Utilities.h"
#include "Item.h"

  char   CustomerOrder::delimiter = '|';
  std::size_t CustomerOrder::fieldWidth = 0;

  CustomerOrder::CustomerOrder (const std::string& record) {
    nOrders = 0;

    Utilities util;
    std::string itemName;
    std::size_t totalSize;
    std::size_t stringPosition = 0;
    bool hasNextToken;

    name = util.nextToken (record, stringPosition, hasNextToken);

    if (name.length () < 1) throw (std::string) "!!! Error: name not specified in record: \n" + record;
    totalSize = name.length ();

    if (hasNextToken) {
      product = util.nextToken (record, stringPosition, hasNextToken);

      if (product.length () < 1) {
        throw (std::string) "!!! Error: product name not specified in record: \n" + record;
      }

      if (product.length () > totalSize) totalSize = product.length ();
    } else throw (std::string) "!!! Error: product name not specified in record: \n" + record;
    if (hasNextToken) {
      std::shared_ptr <ItemOrder> newItem;
      while (hasNextToken) {
        itemName = util.nextToken (record, stringPosition, hasNextToken);
        newItem = std::shared_ptr <ItemOrder> (new ItemOrder (itemName));
        if (newItem->getName ().length () > 0) {_order.push_back (newItem);}

        if (hasNextToken == false){ nOrders = _order.size();}
      }
    } else throw (std::string) "!!! Error: item name not specified in record: \n"+ record;
    if (totalSize > fieldWidth) fieldWidth = totalSize;
  }
  CustomerOrder::CustomerOrder (const CustomerOrder& s) {
    throw (std::string) "!!! Error: no copies are allowed for "+ s.name +" ***";
  }

  CustomerOrder& CustomerOrder::operator = (const CustomerOrder& s) {
    throw (std::string) "!!! Error: no copies are allowed for "+ s.name +" ***";
  }

  CustomerOrder::CustomerOrder (CustomerOrder&& s) {
    this->_order = s._order;
    this->name = s.name;
    this->product = s.product;
    this->nOrders = s.nOrders;
    this->delimiter = s.delimiter;
    this->fieldWidth = s.fieldWidth;
    s._order.clear ();
  }
  CustomerOrder&& CustomerOrder::operator = (CustomerOrder&& s) {
    this->_order = s._order;
    this->name = s.name;
    this->product = s.product;
    this->nOrders = s.nOrders;
    this->delimiter = s.delimiter;
    this->fieldWidth = s.fieldWidth;
    s._order.clear ();
    return std::move(*this);
  }
  CustomerOrder::~CustomerOrder () {}


  unsigned int CustomerOrder::noOrders () const {
    return nOrders;
  }


  const std::string& CustomerOrder::operator [] (unsigned int i) const {
    if (i >= _order.size ()) {
      throw (std::string) "*** Error: Index out of bounds ***";
    }
    return _order [i]->getName ();
  }


  void CustomerOrder::fill (Item& i) {
    for (auto order : _order) if (order->asksFor (i)) {
      order->fill (i.getCode ());
      i++;
    }
  }


  void CustomerOrder::remove (Item& i) {
    for (unsigned int p = 0; p < _order.size (); p++) {
      if (_order [p]->asksFor (i)) _order.erase (_order.begin () + p);
    }
  }


  bool CustomerOrder::empty () const {
    return name.length () < 1;
  }


  void CustomerOrder::display (std::ostream& os) const {
    os << std::setw (fieldWidth) << std::left << name
      << " : "
      << std::setw (fieldWidth) << std::left << product
      << std::endl;
    for (auto order : _order) {
      order->display (os);
      os << std::endl;
    }
  }