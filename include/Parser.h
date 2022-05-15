#pragma once
#include <iostream>
#include <vector>
#include <map>
#include<string>
#include "Polinom.h"
class Lexeme {
private:
	std::string str;
	int type;
public:
	Lexeme(std::string str, int type):str(str), type(type) {

	}

    Lexeme(char str, int type) :str(std::string(1, str)), type(type) {

    }

    Lexeme(double str, int type) :str(std::to_string(str)), type(type) {
        
    }

    int getType() {
        return type;
    }

    friend std::ostream& operator<<(std::ostream& ostr, const Lexeme& s) // вывод
    {

        ostr << s.str;

        return ostr;
    }

    friend class Parser;

};






class Parser {
	std::vector<Lexeme> lex;
	std::string input;
    Polinom pol;
    



    bool IsOperation(char op) {
        if (op == '+' || op == '-' || op == '=')
            return true;
        else
            return false;
    }

    bool IsVariable(char vr) {
        if (vr == 'x' || vr == 'y' || vr == 'z')
            return true;
        else
            return false;

    }

    bool IsAlpha(char ch) {
        if ('0' <= ch && ch <= '9')
            return true;
        else
            return false;
    }


    std::map <char, int> type = { {'+', 0},
                                     {'-', 0},
                                     {'0', 1}, {'^', 3},
            {'x', 2}, {'y', 2}, {'z', 2}


    };


    //здесь и далее реализация конечного автомата

    int pow_x = 0;
    int pow_y = 0;
    int pow_z = 0;
    double coeff = 0;
    std::string current_variable;


    void reset() {
        pow_x = 0;
        pow_y = 0;
        pow_z = 0;
        coeff = 0;
        current_variable = "";

    }


    //функции, которые пойдут в таблицу
    void t_0_0(int i) {
        if (lex[i].str == "+") coeff = 1;
        else coeff = -1;
    }

    void t_0_1(int i) {
        coeff = stod(lex[i].str);
    }

    void t_0_2(int i) {
        current_variable = lex[i].str;
        coeff = 1;
        if (lex[i + 1].str != "^") {
            switch (lex[i].str[0]) {
            case 'x': pow_x = 1; break;
            case 'y': pow_y = 1; break;
            case 'z': pow_z = 1; break;
            }
        }
    }

    void t_1_1(int i) {
        coeff = coeff * stod(lex[i].str);
    }
    
    void t_1_2(int i) {
        current_variable = lex[i].str;
        if (lex[i+1].str!="^") {
            switch (lex[i].str[0]) {
            case 'x': pow_x = 1; break;
            case 'y': pow_y = 1; break;
            case 'z': pow_z = 1; break;
            }
        }
    }


    void t_2_0(int i) {
        pol.add(Monom(coeff,0));
    }

   
    void t_2_2(int i) {
        current_variable = lex[i].str;
        if (lex[i + 1].str != "^") {
            switch (lex[i].str[0]) {
            case 'x': pow_x = 1; break;
            case 'y': pow_y = 1; break;
            case 'z': pow_z = 1; break;
            }
        }
    }

    void t_3_0(int i) {
        if (!(pow_x >= 0 && pow_x < 10 && pow_y >= 0 && pow_y < 10 && pow_z >= 0 && pow_z < 10)) { throw std::invalid_argument("pow of monom is out of range"); }
        pol.add(Monom(coeff, 100 * pow_x + 10 * pow_y + pow_z));
        reset();
        if (lex[i].str == "+") coeff = 1;
        else coeff = -1;
    }

    void t_3_2(int i) {
        current_variable = lex[i].str;
        if (lex[i + 1].str != "^") {
            switch (lex[i].str[0]) {
            case 'x': pow_x += 1; break;
            case 'y': pow_y += 1; break;
            case 'z': pow_z += 1; break;
            }
        }
    }

    void t_3_3(int i) {

    }

    void t_4_1(int i) {
        switch (current_variable[0]) {
        case 'x': pow_x += (int)stod(lex[i].str); break;
        case 'y': pow_y += (int)stod(lex[i].str); break;
        case 'z': pow_z += (int)stod(lex[i].str); break;
        }
    }
    
    void t_5_0(int i) {
        if (!(pow_x >= 0 && pow_x < 10 && pow_y >= 0 && pow_y < 10 && pow_z >= 0 && pow_z < 10)) { throw std::invalid_argument("pow of monom is out of range"); }
        pol.add(Monom(coeff, 100*pow_x+10*pow_y+pow_z));
        reset();
        if (lex[i].str == "+") coeff = 1;
        else coeff = -1;
        

    }


    void t_5_2(int i) {
        current_variable = lex[i].str;
        if (lex[i + 1].str != "^") {
            switch (lex[i].str[0]) {
            case 'x': pow_x += 1; break;
            case 'y': pow_y += 1; break;
            case 'z': pow_z += 1; break;
            }
        }
    }

    //синтаксический анализ
    void syntaxis_analis() {
        std::string tmp_str = input;




        while (tmp_str[0] != '\0') {
            char ch = tmp_str[0];

            if (IsOperation(ch)) {
                lex.push_back(Lexeme(ch, type[ch]));
                tmp_str.erase(tmp_str.begin(), tmp_str.begin() + 1);
            }

            else if (IsAlpha(ch)) {
                std::string::size_type sz;
                lex.push_back(Lexeme(std::stod(tmp_str, &sz), type['0']));
                tmp_str.erase(tmp_str.begin(), tmp_str.begin() + sz);
            }
            else if (IsVariable(ch)) {
                lex.push_back(Lexeme(ch, type[ch]));
                tmp_str.erase(tmp_str.begin(), tmp_str.begin() + 1);
            }

            else if (tmp_str[0] == '^') {
                lex.push_back(Lexeme(ch, type[ch]));
                tmp_str.erase(tmp_str.begin(), tmp_str.begin() + 1);
            }
        }


        lex.push_back(Lexeme("+", 0));


    }


    //лексический анализ
    void lexic_analis() {

        //создаем таблицу состояний и функций, которые соответствую переходам между ними
        std::vector<std::vector<std::pair<int, void (Parser::*)(int a)>>> table(6);

        for (int i = 0; i < table.size(); i++) {
            table[i].resize(4);
            for (int j = 0; j < 4; j++) {
                table[i][j] = std::pair<int, void (Parser::*)(int a)>(-1, 0);
            }
        }
        table[0][0].first = 1; table[0][0].second = &Parser::t_0_0;
        table[0][1].first = 2; table[0][1].second = &Parser::t_0_1;
        table[0][2].first = 3; table[0][2].second = &Parser::t_0_2;

        table[1][1].first = 2; table[1][1].second = &Parser::t_1_1;
        table[1][2].first = 3; table[1][2].second = &Parser::t_1_2;

        table[2][0].first = 1; table[2][0].second = &Parser::t_2_0;
        table[2][2].first = 3; table[2][2].second = &Parser::t_2_2;

        table[3][0].first = 1; table[3][0].second = &Parser::t_3_0;
        table[3][2].first = 3; table[3][2].second = &Parser::t_3_2;
        table[3][3].first = 4; table[3][3].second = &Parser::t_3_3;

        table[4][1].first = 5; table[4][1].second = &Parser::t_4_1;

        table[5][0].first = 1; table[5][0].second = &Parser::t_5_0;
        table[5][2].first = 3; table[5][2].second = &Parser::t_5_2;

        //сама работа конечного автомата
        int status = 0;
        for (int i = 0; i < lex.size(); i++) {
            if (table[status][lex[i].getType()].first != -1) {
                (this->*table[status][lex[i].getType()].second)(i);
                status = table[status][lex[i].getType()].first;
            }
            else {
                std::cout << "in the lexeme number " << i << ": " << lex[i].str << " error";
                throw std::invalid_argument("in the lexeme number " + std::to_string(i) + ": " + lex[i].str + " error");
            }
        }


    }


public:
	Parser(std::string input) {
        input.erase(remove_if(input.begin(), input.end(), isspace), input.end());
        this->input = input;
        syntaxis_analis();
        lexic_analis();
        
	}

    
    Polinom getPolinom() {
        return pol;
    }



	
};
