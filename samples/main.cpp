// ConsoleApplication7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Table.h"
#include "Parser.h"
using namespace std;
int main(){

    HashTable<Polinom> hashtable;
    UnorderedTable<Polinom> unorderedtable;
    OrderedTable<Polinom> orderedtable;


    int n;
    std::cout << "1.work with polinoms\n";
    std::cout << "2.add polinom to table\n";
    std::cout << "3.delete polinom from table\n";
    std::cout << "4.exit\n";
    std::cout << ">>"; std::cin >> n;
    while (n != 4) {

        switch (n) {
        case 1: {
            int flag = 0;
            Polinom pol1;
            do{
                try {
                    flag = 0;
                    std::cout << "1.input first polinom\n";
                    std::cout << "2.get first polinom from unordered table\n";
                    std::cout << "3.get first polinom from ordered table\n";
                    std::cout << "4.get first polinom from hash table\n";
                    std::cout << ">>";

                    int j; std::cin >> j;
                    switch (j) {
                    case 1: {
                        std::cout << "input polinom: ";
                        string a = "";
                        std::cin.clear();
                        std::cin.ignore(std::cin.rdbuf()->in_avail());
                        getline(std::cin, a);
                        pol1 = Parser(a).getPolinom();
                    }
                          break;
                    case 2: {
                        std::cout << "input key\n";
                        int key;
                        std::cin >> key;
                        auto s = unorderedtable.find(key);
                        if (s != 0)
                            pol1 = s->getValue();
                        else {
                            throw std::invalid_argument("error, no element with this key in the table\n");
                        }

                    }
                          break;
                    case 3: {
                        std::cout << "input key\n";
                        int key;
                        std::cin >> key;
                        auto s = orderedtable.find(key);
                        if (s != 0)
                            pol1 = s->getValue();
                        else {
                            throw std::invalid_argument("error, no element with this key in the table\n");
                        }
                    }
                          break;
                    case 4: {
                        std::cout << "input key\n";
                        int key;
                        std::cin >> key;
                        auto s = hashtable.find(key);
                        if (s != 0)
                            pol1 = s->getValue();
                        else {
                            throw std::invalid_argument("error, no element with this key in the table\n");
                        }
                    }
                          break;
                    }
                }
                    
                catch (std::invalid_argument err) {
                    flag = 1;
                    std::cout << err.what() << "\n";
                }
            } while (flag == 1);



            Polinom pol2;
            do {
                try {
                    flag = 0;
                    std::cout << "1.input second polinom\n";
                    std::cout << "2.get second polinom from unordered table\n";
                    std::cout << "3.get second polinom from ordered table\n";
                    std::cout << "4.get second polinom from hash table\n";
                    std::cout << ">>";
                    int t; std::cin >> t;
                    switch (t) {
                    case 1: {
                        std::cout << "input polinom: ";
                        string a = "";
                        std::cin.clear();
                        std::cin.ignore(std::cin.rdbuf()->in_avail());
                        getline(std::cin, a);
                        pol2 = Parser(a).getPolinom();
                    }
                          break;
                    case 2: {
                        std::cout << "input key\n";
                        int key;
                        std::cin >> key;
                        auto s = unorderedtable.find(key);
                        if (s != 0)
                            pol2 = s->getValue();
                        else {
                            throw std::invalid_argument("error, no element with this key in the table\n");
                        }
                    }
                          break;
                    case 3: {
                        std::cout << "input key\n";
                        int key;
                        std::cin >> key;
                        auto s = orderedtable.find(key);
                        if (s != 0)
                            pol2 = s->getValue();
                        else {
                            throw std::invalid_argument("error, no element with this key in the table\n");
                        }
                    }
                          break;
                    case 4: {
                        std::cout << "input key\n";
                        int key;
                        std::cin >> key;
                        auto s = hashtable.find(key);
                        if (s != 0)
                            pol2 = s->getValue();
                        else {
                            throw std::invalid_argument("error, no element with this key in the table\n");
                        }
                    }
                          break;
                    }
                }
                catch (std::invalid_argument err) {
                    flag = 1;
                    std::cout << err.what() << "\n";
                }
            } while (flag == 1);

            Polinom result;

            int d;
            std::cout << "1.multiply polinoms\n";
            std::cout << "2.add polinoms\n";
            std::cout << "3.substract polinoms\n";
            std::cout << "4.to menu\n";
            std::cout << ">>"; std::cin >> d;
            while (d != 4) {
                switch (d) {
                case 1:
                    result = pol1 * pol2;
                    std::cout << result << endl;
                    break;
                case 2:
                    result = pol1 + pol2;
                    std::cout << result << endl;
                    break;
                case 3:
                    result = pol1 - pol2;
                    std::cout << result << endl;
                    break;
                }

                


                int flag = 0;
                do {
                    try {
                        flag = 0;
                        int w;
                        std::cout << "1.add polinom to table\n";
                        std::cout << "2.do nothing\n";
                        std::cout << ">>"; std::cin >> w;
                        if (w == 1) {
                            int key;
                            std::cout << "input key: ";
                            std::cin >> key;
                            unorderedtable.insert(key, result);
                            orderedtable.insert(key, result);
                            hashtable.insert(key, result);
                        }

                    }
                        catch (std::invalid_argument err) {
                            flag = 1;
                            std::cout << "error: " << err.what() << "\n";
                        }

                    } while (flag == 1);
                    
                
              
                        





                std::cout << "1.multiply polinoms\n";
                std::cout << "2.add polinoms\n";
                std::cout << "3.substract polinoms\n";
                std::cout << "4.to menu\n";
                std::cout << ">>"; std::cin >> d;

            }
        }
            break;
        case 2: {

            int key = 0;
            std::cout << "input key\n";
            std::cin >> key;


            std::cout << "input polinom\n";
            string a = "";
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            getline(std::cin, a);



            Polinom pol1 = Parser(a).getPolinom();
            try {
                unorderedtable.insert(key, pol1);
                orderedtable.insert(key, pol1);
                hashtable.insert(key, pol1);
            }
            catch (std::invalid_argument err) {
                std::cout << "error: " << err.what() << "\n";
            }
        }
            break;
        case 3: {
            int key = 0;
            std::cout << "input key\n";
            std::cin >> key;
            try {
                unorderedtable.deleteRecord(key);
                orderedtable.deleteRecord(key);
                hashtable.deleteRecord(key);
                std::cout << "polinom deleted\n";
            }
            catch (std::invalid_argument err) {
                std::cout << "error: " << err.what() << "\n";
            }
        }
              break;

        }
        std::cout << "1.work with polinoms\n";
        std::cout << "2.add polinom to table\n";
        std::cout << "3.delete polinom from table\n";
        std::cout << "4.exit\n";
        std::cout << ">>"; std::cin >> n;
        
    }
    return 0;

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
