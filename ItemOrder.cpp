#include <string>
#include <iomanip>

#include "ItemOrder.h"
#include "Item.h"
#include "Utilities.h"



  ItemOrder::ItemOrder (const std::string& _name) {
    name = _name;
    filled = false;
    code = 0;
  }


  bool ItemOrder::asksFor (const Item& i) const {
    return name == i.getName ();
  }


  bool ItemOrder::isFilled () const {
    return filled;
  }


  void ItemOrder::fill (const unsigned int c) {
    code = c;
    filled = true;
  }


  void ItemOrder::clear () {
    code = 0;
    filled = false;
  }


  const std::string& ItemOrder::getName () const {
    return name;
  }


  void ItemOrder::display (std::ostream& os) const {
    os << (filled ? " + " : " - ") << "["
      << std::setw (CODE_WIDTH) << std::setfill ('0')
      << std::right << (filled ? std::to_string (code) : "0")
      << "] "
      << std::setfill (' ')
      << name;
  }