#pragma once

#include <iostream>
#include <string>

  class Item;

  class ItemOrder {
  private:
    std::string  name;
    bool filled;
    unsigned int code;

  public:

    ItemOrder (const std::string& name= std::string ());
    bool asksFor (const Item& i) const;
    bool isFilled () const;
    void fill (const unsigned int c);
    void clear ();
    const std::string& getName () const;
    void display (std::ostream& o) const;

  };