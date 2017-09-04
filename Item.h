#pragma once

#include <iostream>
#include <string>

  class Item {
  
    std::string   name;
    std::string   source;
    std::string   destination;
    std::string   _details;
    unsigned int  code;
    static char   delimiter;
    static size_t fieldWidth;

  public:
    Item (const std::string& = std::string ());
    bool empty () const;
    void operator++(int);
    unsigned int getCode () const;
    const std::string& getName () const;
    const std::string& getSource () const;
    const std::string& getDestination () const;
    void display (std::ostream& o, bool full = false) const;
    static void setDelimiter (const char d) {
        delimiter = d;
    }
    static size_t getFieldWidth () {
      return fieldWidth;
    }
  };