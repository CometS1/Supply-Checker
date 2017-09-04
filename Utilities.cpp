#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include "Utilities.h"

Utilities::Utilities(){
        
}


Utilities::Utilities(size_t minimum_field_width = 1u){
        field_width = minimum_field_width;
}
     
void Utilities::setFieldWidth(size_t fw){
        field_width = fw;
}
     
size_t Utilities::getFieldWidth() const{
        return field_width;
}
     
const std::string Utilities::nextToken(const std::string& str, size_t& next_pos, bool& more){
        std::string go = "";
        std::string check = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
        size_t first, last, firstspace, lastspace;
        go = str.substr (next_pos);
        next_pos = (go.find(getDelimiter()) + 1) + next_pos;

        if (go.find(getDelimiter()) == std::string::npos){

                more = false;
        }
        else{
                go = go.substr(0, go.find(getDelimiter()));
                if (go == ""){
                        throw std::string("<-- *** no token found before the delimiter ***");
                }
                more = true;
        }
        first = go.find_first_of(check);
        last = go.find_last_of(check) + 1;
        if (first != std::string::npos && last != std::string::npos){
                go = go.substr(first, last);
        }
        else go = "";

        while ((last - first != go.length()) && first != std::string::npos && last != std::string::npos){
                first = go.find_first_of(check);
                last = go.find_last_of(check) + 1;
                go = go.substr(first, last);
        }

        if (field_width < go.length()){
                setFieldWidth(go.length());
        }

        return go;
}
     
void Utilities::setDelimiter(const char c){
        Utilities::delimiter = c;
}
     
const char Utilities::getDelimiter(){
        return Utilities::delimiter;
}

char Utilities::delimiter = '|';