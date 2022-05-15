#pragma once
#include<iostream>

template <class TElement>
struct Node {
	TElement data;
	struct Node* next;
	Node(TElement Data, Node* Next) : data(Data), next(Next) {
	}
};



template<class TElement>
class ListIterator : public std::iterator<std::input_iterator_tag, Node <TElement>>
{
private:
	ListIterator(Node <TElement>* p) :p(p) {}
	Node <TElement>* p;
public:
	ListIterator(const ListIterator& it) : p(it.p) {}

	bool operator!=(ListIterator const& other) const {
		return p != other.p;
	}
	bool operator==(ListIterator const& other) const {
		return p == other.p;
	}//need for BOOST_FOREACH

	TElement& operator*() const {
		return p->data;
	}


	ListIterator next() const{
		return ListIterator(p->next);
	}


	ListIterator& operator++() {
		p = p->next;
		return *this;
	}

	ListIterator operator++(int) {
		ListIterator t(*this);
		operator++();
		return t;
	}

	template<class P>
	friend class TList;

};


template <class TElement>
class TList
{
private:
	unsigned int sizeOfList;
	Node <TElement>* first;
	Node <TElement>* last;
public:


	TList() :sizeOfList(0), first(0), last(0) {
	}


	TList(TList const& a) {
		sizeOfList = 0;
		first = 0;
		last = 0;
		if (a.sizeOfList != 0) {
			sizeOfList = a.sizeOfList;
			Node <TElement>* temp = a.first;
			Node <TElement>* t = new Node<TElement>(temp->data, 0);
			first = t;
			temp = temp->next;
			while (temp != 0) {

				t->next = new Node<TElement>(temp->data, 0);
				t = t->next;
				temp = temp->next;
			}


			temp = a.first;
			while (temp -> next != 0) {
				temp = temp->next;
			}
			last = temp;

		}
	}




	TList& operator=(const TList& a) {
		if (this != &a) {

			clear();
			sizeOfList = 0;
			if (a.sizeOfList != 0) {
				sizeOfList = a.sizeOfList;
				Node <TElement>* temp = a.first;
				Node <TElement>* t = new Node<TElement>(temp->data, 0);
				first = t;
				temp = temp->next;
				while (temp != 0) {

					t->next = new Node<TElement>(temp->data, 0);
					t = t->next;
					temp = temp->next;
				}
			}
		}
		return *this;
	}





	~TList() {
		clear();
	}

	void push_top(const TElement element) {
		Node<TElement>* node = new Node <TElement>(element, first);
		if (empty()) {
			first = new Node <TElement>(element, first);
			last = first;
			
		}
		else{
			Node<TElement>* t = new Node <TElement>(element, first);
			first = t;
		}
		sizeOfList++;
	}

	void push_back(const TElement element) {
		Node<TElement>* t = new Node<TElement>(element,0);
		if(empty()){
			first = t;
			last = t;
		}
		else{
			last->next = t;
			last = t;
		}
		sizeOfList++;

	}

	void erase(ListIterator<TElement> t) {
		if (t.p == 0) { 
			if (sizeOfList == 0) throw std::invalid_argument("list is empty");
			remove_first();
			return;
		}
		Node<TElement>* f = t.p->next;
		t.p->next = t.p->next->next;
		delete f;
		sizeOfList--;
		
	}



	ListIterator<TElement> begin() const {
		
		return ListIterator<TElement>(first);
	}



	ListIterator<TElement> end() const{
		return ListIterator<TElement>(0);
	}
	


	void remove_first() {
		if (empty()) { throw std::invalid_argument("list is empty"); }
		
		if (first == last) {
			last = 0;
		}
		Node<TElement>* t = first;
		first = first->next;
		sizeOfList--;
		delete t;

	}


	void remove_last() {
		if (empty()) { throw std::invalid_argument("list is empty"); }

		if (first == last) {
			last = 0;
			delete first;
			first = 0;
			sizeOfList--;
		}
		else {
			Node<TElement>* t = first;
			while (t->next != last) t = t->next;
			t->next = 0;
			delete last;
			last = t;
			sizeOfList--;
		}
		
	}

	void insert(ListIterator<TElement> t, const TElement& data) {
		Node<TElement>* f = t.p;
		if (f==0) {
			push_top(data);
		}
		else {
			f->next = new Node<TElement>(data, f->next);
			sizeOfList++;
		}
		
	}


	TElement& operator[] (const int index) {
		if (index>=sizeOfList) throw std::invalid_argument("invalid_argument");
		Node<TElement>* p = first;
		for (int i = 0; i < index; i++) {
			p = p->next;
		}
		return p->data;
	}


	void clear() {
		auto it = first;
		while (it != 0) {
			auto p = it;
			it = it->next;
			delete p;
		}
	}


	void pop() {
		if (sizeOfList == 0) throw std::invalid_argument("pop out of empty list");
		sizeOfList--;
		Node<TElement>* temp = first;
		first = first->next;
		delete temp;
	}


	int GetSize() {
		return sizeOfList;
	}


	bool empty() {
		return sizeOfList == 0;
	}


	friend std::ostream& operator<<(std::ostream& ostr, const TList& s) // вывод
	{

		Node<TElement>* t = s.first;

		while (t != 0) {
			ostr << t->data << " ";
			t = t->next;
		}

		return ostr;
	}


	template <class T>
	friend bool operator==(const TList<T>& lhs, const TList<T>& rhs);


};


template <class TElement>
bool operator==(const TList<TElement>& lhs, const TList<TElement>& rhs) {
	if (&lhs != &rhs) {
		if (lhs.sizeOfList == rhs.sizeOfList) {
			Node <TElement>* it = lhs.first;
			Node <TElement>* at = rhs.first;
			while (it != 0) {
				if (it->data != at->data)
					return false;
				it = it->next;
				at = at->next;
			}
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return true;
	}
}



