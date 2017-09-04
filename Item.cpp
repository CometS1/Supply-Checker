#include <iomanip>
#include "Item.h"
#include "Utilities.h"

  char   Item::delimiter = '|';
  std::size_t Item::fieldWidth = 0;

  Item::Item (const std::string& record) {
    _details = "no _detailsed description";
    code = 1;

    Utilities util;
    bool hasNextToken = true;
    std::size_t stringPosition = 0;
    std::size_t totalSize;

    name = util.nextToken (record, stringPosition, hasNextToken);
    if (name.length () < 1) throw (std::string) "!!! Error: name not specified in record: \n" + record;
    totalSize = name.length ();

    if (hasNextToken) {
      source = util.nextToken (record, stringPosition, hasNextToken);
    } else throw (std::string) "!!! Error: source not specified in record: \n" + record;

    if (hasNextToken) {
      destination = util.nextToken (record, stringPosition, hasNextToken);
    } else throw (std::string) "!!! Error: destination not specified in record: \n" + record;

    // Extracting code
    if (hasNextToken) {
      std::string _code = util.nextToken (record, stringPosition, hasNextToken);

        try {
       code = std::stol (_code);
      } catch (...) {
        throw (std::string) "!!! Error: invalid code for item (" + _code + ") ***";
      }
    }
    if (hasNextToken) {
      std::string details = util.nextToken (record, stringPosition, hasNextToken);
      if (details.length () > 0) {
                _details = details;
        }
        else{
                _details = "no detailed description";
        }
    }

    // Setting the maximum field width
    if (totalSize > fieldWidth) fieldWidth = totalSize;
  }


  bool Item::empty () const {
    return name == "";
  }


  void Item::operator ++ (int) {
    code++;
  }


  unsigned int Item::getCode () const {
    return code;
  }


  const std::string& Item::getName () const {
    return name;
  }


  const std::string& Item::getSource () const {
    return source;
  }


  const std::string& Item::getDestination () const {
    return destination;
  }


  void Item::display (std::ostream& os, bool full) const {
    os << std::left << std::setw (fieldWidth) << name
      << std::right << std::setfill ('0')
      << " ["
      << std::setw (CODE_WIDTH) << std::to_string (code)
      << "] "
      << std::setfill (' ');

    if (full) {
      os << "From " << std::setw (fieldWidth) << std::left << name
        << " To "  << std::setw (fieldWidth) << std::left << destination
        << std::endl
        << std::setw (fieldWidth + CODE_WIDTH + 2) << " "
        << std::left << ": "+ _details;
    }

    os << std::endl;
  }