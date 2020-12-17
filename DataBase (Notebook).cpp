// studentsDB.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

struct Notebook {
    int number;
    char surname[32];
    char name[16];
    char np[16];
    char email[32];
    char db;
};
struct DB {
    DB* next;
    Notebook list;
};
struct List {
    DB* first, * last;
};
struct TIME {
    int tm_mday;  
    int tm_mon;   
    int tm_year;  
};
void createDB(List& l) {
    l.first = l.last = nullptr;
}
void add_to_Note_book(List& l, const Notebook& x, int& count) {
    DB* tmp = new DB;
    tmp->list = x;
    tmp->next = nullptr;
    if (l.first == nullptr) {
        l.first = l.last = tmp;
    }
    else {
        l.last->next = tmp;
        l.last = tmp;
    }
    ++count;
}
void Delete(List& l, int& count) {
    std::cout << "Surname: ";
    char tmp[32];
    std::cin >> tmp; std::cin.ignore();
    DB* now = l.first;
    int i = 0;
    while (now->next != nullptr) {
        if (strcmp(tmp, now->next->list.surname) == 0) {
            now->next = now->next->next;
            --count;
            return;
        }
        else {
            now = now->next;
        }
    }
    if (strcmp(tmp, now->list.surname) == 0) {
        delete now;
        createDB(l);
        return;
    }
    std::cout << "There is no number : " << tmp << std::endl;
}
 void delete_from_Notebook(List& l) {
    DB* tmp;
    while (l.first) {
        tmp = l.first;
        l.first = l.first->next;
        delete tmp;
    }
    l.first = l.last = nullptr;
}

 std::ostream& operator << (std::ostream& out, const Notebook& X) {
     out << X.number << ". " << X.surname << " " << X.name << "  +" << X.np << " " << X.email << " " << X.db << "." << X.db << "." << X.db;
     return out;
 }
 std::ostream& operator << (std::ostream& out, const TIME& X) {
     out << X.tm_year << "." << X.tm_mon << "." << X.tm_mday;
     return out;
 }
 std::istream& operator >> (std::istream& in, Notebook& X) {
     std::cout << "Input Student number: ";
     in >> X.number; in.ignore();
     std::cout << "Input Surname: ";
     in.getline(X.surname, 32);
     std::cout << "Input Name: ";
     in.getline(X.name, 16);;
     std::cout << "Input Number Phone : ";
     in >> X.np; in.ignore();
     std::cout << "Input Email: ";
     in.getline(X.email, 32);
     std::cout << "Input date of birthday" << std::endl;
     std::cout << "Input Year : ";
     in >> X.db; in.ignore();
     std::cout << "Input Month : ";
     in >> X.db; in.ignore();
     std::cout << "Input Day: ";
     in >> X.db; in.ignore();
     std::cout << std::endl;
     return in;
 }
 std::ostream& operator << (std::ostream& out, const List& L) {
     DB* now = L.first;
     while (now) { 
         out << now->list << std::endl;
         now = now->next;
     }
     return out;
 }
 bool operator <(const DB& X, const DB& Y) {
     int res = strcmp(X.list.surname, Y.list.surname);
     if (res < 0)
         return true;
     if (res == 0) {
         if (strcmp(X.list.name, Y.list.name) < 0)
             return true;
     }
     return false;

 }
 bool comp(const DB& X, const DB& Y, const TIME& l) {
     int N = 30 * (l.tm_mon - 1) + l.tm_mday;
     int a, k;
     int b = 30 * (X.list.db - 1) + X.list.db;
     int c = 30 * (Y.list.db - 1) + Y.list.db;
     if (N < b) {
         a = N - b;
     }
     else {
         if (l.tm_year % 4 == 0)a = 361 - N + b;
         else a = 360 - N + b;
     }
     if (N < c) {
         k = N - c;
     }
     else {
         if (l.tm_year % 4 == 0)k = 359 - N + c;
         else k = 360 - N + c;
     }
     return a < b;
 }  
 void np(const List& l) {
     std::cout << "Number Phone: ";
     std::string tmp;
     std::cin >> tmp; std::cin.ignore();
     DB* now = l.first;
     while (now) {
         if (tmp == now->list.np) {
             std::cout << now->list << std::endl;
             return;
         }
         else {
             now = now->next;
         }
     }
     std::cout << "There is no number : " << tmp << std::endl;

 }
 void Surname(const List& l) {
     std::cout << "Surname: ";
     char tmp[32];
     std::cin >> tmp;
     DB* now = l.first;
     while (now) {
         if (strcmp(tmp, now->list.surname) == 0) {
             std::cout << now->list << std::endl;
             return;
         }
         else {
             now = now->next;
         }
     }
     std::cout << "There is no number : " << tmp << std::endl;
 }
 void saveDB(List& DB1, int count) {
     char fname[256];
     std::cout << "Database file name : " << std::endl;
     std::cin.getline(fname, 256);
     if (strlen(fname) < 1)
         strcpy_s(fname, "students.db");

     std::ofstream outFile;
     outFile.open(fname, std::ios_base::binary);
     if (!outFile) {
         std::cout << "Can not open file " << fname << std::endl;
         return;
     }
     int count1 = count;
     DB* tmp = DB1.first;
     while (count1--) {
         outFile.write((char*)&(tmp->list), sizeof(Notebook));
         tmp = tmp->next;
     };
     outFile.close();
 }

 void openDBfile(List& l, int& count) {
     char fname[256];
     std::cout << "Database file name : ";
     std::cin.getline(fname, 256);
     if (strlen(fname) < 1)
         strcpy_s(fname, "numbers.db");
     std::ifstream inFile;
     inFile.open(fname, std::ios_base::binary);
     if (!inFile) {
         std::cout << "Can not open file " << fname << std::endl;
         return;
     }
     delete_from_Notebook(l);
     count = 0;
     Notebook tmp;
     while (inFile.peek() != EOF) {
         inFile.read((char*)&tmp, sizeof(tmp));
         add_to_Note_book(l, tmp, count);
     }
     inFile.close();
     std::cout << "Database " << fname << " is opened. Total " << count << " records." << std::endl;
 }
 void sortBySurname(List& L) {
     bool isSorted = true;
     DB* now, * prev;
     do {
         isSorted = true;
         prev = nullptr;
         now = L.first;
         while (now->next) {
             if (now->next < now) {
                 if (prev != nullptr) {
                     prev->next = now->next;
                     now->next = now->next->next;
                     prev->next->next = now;
                     prev = prev->next;
                 }
                 else {
                     L.first = now->next;
                     now->next = now->next->next;
                     L.first->next = now;

                     prev = L.first;
                 }
                 isSorted = false;
             }
             else {
                 prev = now;
                 now = now->next;
             }
         }
     } while (!isSorted);
     
     now = L.first;
     while (now->next) {
         now = now->next;
     }
     L.last = now;
 }
 void SortbyDoB(List& L) {
     bool isSorted = true;
     DB* now, * prev;
     do {
         isSorted = true;
         prev = nullptr;
         now = L.first;

         while (now->next) {

             bool s1 = now->next->list.db < now->list.db;
             bool s2 = now->next->list.db < now->list.db;
             bool s3 = now->next->list.db < now->list.db;

             if (s1 || (!s1 && s2) || (!s1 && !s2 && s3)) {
                 if (prev != nullptr) {
                     prev->next = now->next;
                     now->next = now->next->next;
                     prev->next->next = now;
                     prev = prev->next;
                 }
                 else {
                     L.first = now->next;
                     now->next = now->next->next;
                     L.first->next = now;

                     prev = L.first;
                 }
                 isSorted = false;
             }
             else {
                 prev = now;
                 now = now->next;
             }
         }
     } while (!isSorted);
     
     now = L.first;
     while (now->next) {
         now = now->next;
     }
     L.last = now;
 }
 void SortbyDtB(List& L, const TIME& l) {
     bool isSorted = true;
     DB* now, * prev;
     do {
         isSorted = true;
         prev = nullptr;
         now = L.first;
         while (now->next) {

             if (
                 comp(*now->next, *now, l)) {
                 if (prev != nullptr) {
                     prev->next = now->next;
                     now->next = now->next->next;
                     prev->next->next = now;
                     prev = prev->next;
                 }
                 else {
                     L.first = now->next;
                     now->next = now->next->next;
                     L.first->next = now;

                     prev = L.first;
                 }
                 isSorted = false;
             }
             else {
                 prev = now;
                 now = now->next;
             }
         }
     } while (!isSorted);
    
     now = L.first;
     while (now->next) {
         now = now->next;
     }
     L.last = now;
 }
 TIME Time() {
     TIME nowT;
     std::cout << "Input in today's day of the month : ";
     std::cin >> nowT.tm_mday;
     std::cout << "Input the current month : ";
     std::cin >> nowT.tm_mon;
     std::cout << "Input the current year : ";
     std::cin >> nowT.tm_year;
     std::cout << std::endl;
     return nowT;
 }
 
 int menu() {
    for (int i = 0; i < 20; ++i)
        std::cout << '*';
    std::cout << std::endl;
    std::cout << "1. Add to notebook" << std::endl;
    std::cout << "2. Delete to notebook" << std::endl;
    std::cout << "3. Save  to notebook" << std::endl;
    std::cout << "4. Export notebook to file" << std::endl;
    std::cout << "5. Sort by last name" << std::endl;
    std::cout << "6. Sort by date of birth" << std::endl;
    std::cout << "7. Sort by number of days before birth" << std::endl;
    std::cout << "8. Search by last name" << std::endl;
    std::cout << "9. Search by phone number" << std::endl;
    std::cout << "0.Exit" << std::endl;
    int tmp;
    std::cin >> tmp;
    std::cin.ignore();
    return tmp;
}



int main()
{
    List group;
    createDB(group);
    int action;
    Notebook tmp;
    int count = 0;
    TIME time = Time();
    do {

        action = menu();
        switch (action) {
        case 1: {
            std::cin >> tmp;
            add_to_Note_book(group, tmp, count);
            std::cout << tmp << std::endl;
            break;
        };
        case 2: {
            Delete(group, count);
            break;
        }
        case 3: {
            std::cout << group << std::endl;
            break;
        }
        case 4: {
            int y = menu();
            switch (y) {
            case 1: {
                sortBySurname(group);
                break;
            }
            case 2: {
                SortbyDoB(group);
                break;
            }
            case 3: {
                SortbyDtB(group, time);
                break;
            }
            }
            break;
        }
        case 5: {
            saveDB(group, count);
            break;
        }
        case 6: {
            int k;
            k = menu();
            switch (k) {
            case 1: {
                np(group);
                break;
            }
            case 2: {
                Surname(group);
                break;
            }
            }
            break;
        }
        case 7: {
            openDBfile(group, count);
        }

        }

    } while (action != 0);
}
