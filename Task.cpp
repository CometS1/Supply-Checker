#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include "Task.h"
#include "Utilities.h"

Task::Task(){

}

Task::Task(const std::string& record){
        //name = record;
        nextTask[0] = "";
        nextTask[1] = "";
        bool more = true;
        size_t next_pos = 0;
        slots = "1";

        Utilities util(getFieldWidth());
        name = util.nextToken(record, next_pos, more);
        pNextTask[0] = nullptr;
        pNextTask[1] = nullptr;

        if (name == ""){
                throw std::string("<-- *** no token found before the delimiter ***");
        }
        if (more == true){
                slots = util.nextToken(record, next_pos, more);

        }
        if (more == true){
                nextTask[0] = util.nextToken(record, next_pos, more);
        }
        if (more == true){
                nextTask[1] = util.nextToken(record, next_pos, more);
        }

        if (more == true){
                name == "";
        }

        if (field_width < name.length()){
                        field_width = name.length();
        }
        if (field_width < slots.length()){
                        field_width = slots.length();
        }
        if (field_width < nextTask[0].length()){
                        field_width = nextTask[0].length();;
        }
        if (field_width < nextTask[1].length()){
                        field_width = nextTask[1].length();
        }

}
     
const std::string& Task::getName() const{
        return name;
}
     
unsigned int Task::getSlots() const{
        int num = std::stoul(slots);
        return num;
}
     
bool Task::validate(const Task& task){
        bool check = false;
        bool check1, check2 = false;
        check1 = (nextTask[0] == task.getName());
        if (check1){
                pNextTask[0] = &task;
        }
        if (nextTask[0] == "" && nextTask[1] == ""){
                check = true;
        }
        if (nextTask[1] != ""){
                //std::cout << nextTask[1] << std::endl;
                check2 = nextTask[1] == task.getName();
                if (check2){
                        pNextTask[1] = &task;
                }
                if (pNextTask[0] != nullptr && pNextTask[1] != nullptr){
                        check = true;
                }
        }
        else{
                if (pNextTask[0] != nullptr){
                        check = true;
                }
        }
        return check;
}
     
const Task* Task::getNextTask(Quality quality) const{
        int num = 0;
        if (quality == passed){num = 0;}
        else if(quality == redirect){num = 1;}
        if (pNextTask[num] == nullptr){
                std::string error = "*** Validate  [" + nextTask[0] + "] @ [" + getName() + "] ***";
                throw (error);
        }
        return pNextTask[num];
}
     
void Task::display(std::ostream& os) const{
        std::string na, sl, next1;
        na = "[" + getName() + "]";
        os << "Task Name    : " << std::left << std::setw(field_width + 2) << na << std::setw(4) << std::right << "[" << slots << "]" << std::endl;
        if (nextTask[0] != ""){
                if (pNextTask[0] != nullptr){
                        next1 =  "[" + pNextTask[0]->getName() + "]";
                        os << " Continue to : " << std::left << std::setw(field_width + 2) << next1 << std::endl;

                }
                else{
                        next1 = "[" + nextTask[0] + "]";
                        os << " Continue to : " << std::left << std::setw(field_width + 2) << next1 << std::setw(4) << std::right << "*** to be validated ***"  << std::endl;
                }
        }
        if (nextTask[1] != ""){
                if (pNextTask[1] != nullptr){
                        next1 =  "[" + pNextTask[1]->getName() + "]";
                        os << " Redirect to : " << std::left << std::setw(field_width + 2) << next1 << std::endl;

                }
                else{
                        next1 = "[" + nextTask[1] + "]";
                        os << " Redirect to : " << std::left << std::setw(field_width + 2) << next1 << std::setw(4) << std::right << "*** to be validated ***"  << std::endl;
                }
        }
}
     
void Task::setDelimiter(const char c){
        Task::delimiter = c;
}
     
size_t Task::getFieldWidth(){
        return Task::field_width;
}
 
bool operator==(const Task& a, const Task& b){
        a.getName() == b.getName();
        return true;
}

char Task::delimiter = '|';
size_t Task::field_width = 1u;