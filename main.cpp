#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
bool overflow ( ){

    if (! std::cin){
        std::cout <<"Input error.Enter again: ";
        std::cin.clear();
        std::cin.ignore(1000, '\n');

        return true;
    } else {return false;}
}
void EnterBirthday (vector <string> &name, vector <tm> &date, string s,int i){
    date.resize (date.size () +1);
    name.push_back (s);

    cout << "Enter date: ";
    std::time_t t = std::time(nullptr);
    date[i] = *std::localtime(&t);
    cin >> get_time(&date [i],"%Y/%m/%d");
    while (overflow ()) {cin >> get_time(&date [i],"%Y/%m/%d");}
}

int main() {
    vector <string> name;
    vector <tm> date;
    for (int i = 0;;i++){ // Ввод дат
        string temp;
        cout << "Enter name: ";
        cin >>  temp;
        while(overflow()){cin >> temp;}

        if (temp == "end") {break;}

        EnterBirthday (name,date,temp,i);

    }
    time_t t = std::time(nullptr);
    tm now = *std::localtime (&t);

    // проверка дня
    int minDay = 31;
    int minMonth = 12;
    for (int i = 0; i <name.size ();i++){
        tm birthday = date[i];

        if(birthday.tm_mday == now.tm_mday && birthday.tm_mon == now.tm_mon) {
            cout << name[i] << " has a birthday today!\n";
        }else if(birthday.tm_year - now.tm_year < 0 ) { // если убрать else будет включать сегодняшних именинников как,
            if (birthday.tm_mon - now.tm_mon > 0) {     //самые ближайшие
                if (minMonth > birthday.tm_mon ){
                    minMonth = birthday.tm_mon;
                }
                if (birthday.tm_mon == minMonth && birthday.tm_mday - minDay < 0) {
                    minDay = birthday.tm_mday;
                }
            }else if (birthday.tm_mon - now.tm_mon == 0){
                if(birthday.tm_mon < minMonth) {
                    minMonth = birthday.tm_mon;
                    minDay = birthday.tm_mday;
                }else if (birthday.tm_mon == minMonth){
                    if (birthday.tm_mday - now.tm_mday > 0){
                        minDay = birthday.tm_mday;
                    }
                }
            }
        }
    }

    for (int i = 0; i <name.size ();i++){
        if (date[i].tm_mday == minDay && date[i].tm_mon == minMonth){
            cout << name[i] << " has nearest birthday " <<put_time(&date[i],"%m/%d")<<endl;
        }
    }


}
