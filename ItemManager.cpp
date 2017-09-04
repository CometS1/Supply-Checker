// Manager Milestone - ItemManager Interface
// ItemManager.cpp
// Chris Szalwinski
// v1.0 - 16/11/2015
#include <iostream>
#include <vector>
#include "ItemManager.h"

        void ItemManager::push_back(Item&& item){
         items.push_back(std::move(item));
        }

        std::vector<Item>::iterator ItemManager::begin(){
         return items.begin();
         
        }

        std::vector<Item>::iterator ItemManager::end(){
         return items.end();
         
        }

        const std::vector<Item>::const_iterator ItemManager::cbegin() const{
         return items.begin();
         
        }

        const std::vector<Item>::const_iterator ItemManager::cend() const{
         return items.end();
         
        }

        void ItemManager::display(std::ostream& os, bool desc) const{
                for (const Item& item : items)
                        item.display(os, desc);

        }