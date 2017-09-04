// Manager Milestone - TaskManager Interface
// TaskManager.cpp
// Chris Szalwinski
// v1.0 - 16/11/2015
#include <iostream>
#include <vector>
#include <algorithm>
#include "TaskManager.h"
         void TaskManager::push_back(Task&& task){
                 tasks.push_back(std::move(task));
         }
         
         std::vector<Task>::iterator TaskManager::begin(){
                 return tasks.begin();
                 
         }
         
         std::vector<Task>::iterator TaskManager::end(){
                 return tasks.end();
                 
         }
         
         const std::vector<Task>::const_iterator TaskManager::cbegin() const{
                 return tasks.begin();
                 
         }
         
         const std::vector<Task>::const_iterator TaskManager::cend() const{
                 return tasks.end(); 
         }
         
         void TaskManager::validate(std::ostream& os){
                bool valid = true;
                for (Task& task : tasks) {
                        bool invalid = true;
                        for (auto j = 0u; j < tasks.size() && invalid; j++) {
                                if (task.validate(tasks[j]))
                                        invalid = false;
                        }
                        valid = !invalid;
                }
         }
         
         void TaskManager::display(std::ostream& os) const{
                 for (const Task& task : tasks)
                         task.display(os);
         }

        void validate(const TaskManager& taskMan, const ItemManager& itemMan, std::ostream& os){
                std::string source;
                std::string destination;
                std::string name;

                for (auto itemIt = itemMan.cbegin(); itemIt != itemMan.cend(); itemIt++) {
                        source = itemIt->getSource();
                        destination = itemIt->getDestination();
                        name = source;

                        std::vector<Task>::const_iterator sourceIt = std::find_if
                                (taskMan.cbegin(), taskMan.cend(),
                                [&](Task task) { return name == task.getName(); });

                        if (sourceIt == taskMan.cend()){
                                os << name << " is unavailable\n";
                        }


                        name = destination;
                        std::vector<Task>::const_iterator destIt = std::find_if 
                                (taskMan.cbegin(), taskMan.cend(), 
                                [&](Task task) { return task.getName() == name; });

                        if (destIt == taskMan.cend())
                                os << name << " is unavailable\n";
                }
        }