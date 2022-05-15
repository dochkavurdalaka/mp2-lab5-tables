#pragma once
#include "TList.h"
class Monom {
private:
	double coeff;
	int index;
public:
	Monom(double coeff, int index):coeff(coeff),index(index)
	{
		if (!((index >= 0 && index <= 999) || index == -1)) throw std::invalid_argument("invalid argument");
	}

	Monom operator-() const {
		return Monom(-coeff, index);
	}



	friend std::ostream& operator<<(std::ostream& ostr, const Monom& s) // вывод
	{
		if (s.coeff == 0) ostr << "0";
		else {
			if (abs(s.coeff) != 1) ostr << s.coeff; else { if (s.coeff == -1)  ostr << "-"; }
 
			if (s.index / 100 != 0) { if (s.index / 100 != 1) ostr << "x^" << s.index / 100; else ostr << "x"; }
			if (s.index % 100 / 10 != 0) { if (s.index % 100 / 10 != 1) ostr << "y^" << s.index % 100 / 10; else ostr << "y"; }
			if (s.index % 10 != 0) { if (s.index % 10 != 1) ostr << "z^" << s.index % 10; else ostr << "z"; }

		}

		return ostr;
	}

	friend class Polinom;
	friend inline bool operator< (const Monom& lhs, const Monom& rhs);
	friend inline bool operator== (const Monom& lhs, const Monom& rhs);
	friend inline bool operator== (const Monom& lhs, const Monom& rhs);
	friend inline bool operator!= (const Monom& lhs, const Monom& rhs);
	friend Monom operator+(Monom lhs, const Monom& rhs);
	friend Monom operator*(Monom lhs, const Monom& rhs);
	friend Polinom operator+(const Polinom& lhs, const Polinom& rhs);
	friend Polinom operator*(const Polinom& lhs, const Polinom& rhs);
	friend std::ostream& operator<<(std::ostream& ostr, const Polinom& s);
};


inline bool operator< (const Monom& lhs, const Monom& rhs) { return lhs.index < rhs.index; }
inline bool operator> (const Monom& lhs, const Monom& rhs) { return  operator < (rhs, lhs); }
inline bool operator== (const Monom& lhs, const Monom& rhs) { return lhs.index == rhs.index; }
inline bool operator!= (const Monom& lhs, const Monom& rhs) { return lhs.index != rhs.index; }
Monom operator+(Monom lhs, const Monom& rhs) { 
	if (lhs.index != rhs.index) throw std::invalid_argument("invalid_argument");
	lhs.coeff += rhs.coeff;
	return lhs;
}

Monom operator*(Monom lhs, const Monom& rhs) {
	
	lhs.coeff *= rhs.coeff;
	lhs.index += rhs.index;
	return lhs;
}


class Polinom {
private:
	TList<Monom> pol;
	
public:
	Polinom() {
		pol.push_back(Monom(0,-1));
	}


	Polinom(Polinom const& a){
		pol=a.pol;
	}


	//максимально важная функция: add, добавляет моном в полином, так, чтобы полином оставался отсортированным.
	//Если в полиноме моном с такой же степенью, но отрицательным коэффициентом, то этот моном занулится и исчезнет из списка
	//если передадим моном с нулевым коэффициентом, то он не добавится в полином

	void add(Monom t) {

		if (t.coeff == 0) return;

		auto it = pol.begin();
		for (; it.next() != pol.end() && t < *it.next(); it++){}
		if (it.next() != pol.end()) {
			if (t != *(it.next())) {
				pol.insert(it, t);
			}
			else {
				(*it.next()).coeff = (*it.next()).coeff + t.coeff;
				if ((*it.next()).coeff == 0)
					pol.erase(it);
			}
		}
		else {
			pol.insert(it, t);
		}
	}


	Polinom operator-() const {

		Polinom temp(*this);
		for (auto it = temp.pol.begin().next(); it != temp.pol.end(); it++)
			*it = -(*it);
		return temp;
	}


	friend std::ostream& operator<<(std::ostream& ostr,const Polinom& s) // вывод
	{


		if (s.pol.begin().next() != s.pol.end()) {
			ostr << *s.pol.begin().next();


			for (auto it = s.pol.begin().next().next(); it != s.pol.end(); it++) {
				if ((*it).coeff > 0) {
					ostr << "+" << *it;
				}
				else {
					ostr << *it;
				}
			}
		}
		if(s.pol.begin().next() == s.pol.end()) {
			ostr << "0";
		}


		return ostr;
	}

	Monom operator[] (const int index) {

		return pol[index+1];
	}


	

	friend Polinom operator+(const Polinom& lhs, const Polinom& rhs);
	friend Polinom operator*(const Polinom& lhs, const Polinom& rhs);
	friend bool operator==(const Polinom& lhs, const Polinom& rhs);
};

Polinom operator+(const Polinom& lhs, const Polinom& rhs) {
	Polinom temp;

	auto lt = ++lhs.pol.begin();
	auto rt = ++rhs.pol.begin();
	while (lt != lhs.pol.end() && rt != rhs.pol.end()) {
		if ((*lt) > (*rt)) {
			temp.pol.push_back(*lt);
			lt++;
		}
		else {
			if ((*lt) < (*rt)) {
				temp.pol.push_back(*rt);
				rt++;
			}
			else {
				int coeff = (*lt).coeff + (*rt).coeff;
				if(coeff!=0){
					temp.pol.push_back(Monom(coeff, (*lt).index));
					lt++;
					rt++;
				}
				else {
					lt++;
					rt++;
				}
			}
		}
	}

	if (lt == lhs.pol.end()) {
		for(;rt != rhs.pol.end();rt++)
			temp.pol.push_back(*rt);
	}
	else {
		for (; lt != lhs.pol.end(); lt++)
			temp.pol.push_back(*lt);
	}



	return temp;
}


Polinom operator-(const Polinom& lhs, const Polinom& rhs) {

	return (lhs+(-rhs));
}


Polinom operator*(const Polinom& lhs, const Polinom& rhs) {

	if (rhs.pol.begin().next() == rhs.pol.end() || lhs.pol.begin().next() == lhs.pol.end()) return Polinom();


	int lt = (*lhs.pol.begin().next()).index;
	int rt = (*rhs.pol.begin().next()).index;


	if (((lt % 10) + (rt % 10) > 9) || (((lt % 100 / 10) + (rt % 100 / 10)) > 9) || (((lt / 100) + (rt / 100)) > 9)) throw std::invalid_argument("multiply_of_polinoms_out_of_range");



	Polinom temp;
	for (auto lt = lhs.pol.begin().next(); lt != lhs.pol.end(); lt++)
		for (auto rt = rhs.pol.begin().next(); rt != rhs.pol.end(); rt++) 
			temp.add((*rt) * (*lt));
		
	return temp;
}

bool operator==(const Polinom& lhs, const Polinom& rhs) {
	return lhs.pol == rhs.pol;
}

bool operator!=(const Polinom& lhs, const Polinom& rhs) {
	return !(lhs == rhs);
}