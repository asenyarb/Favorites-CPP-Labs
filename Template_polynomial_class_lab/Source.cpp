#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include "KRat.h"
using namespace std;
template <typename T> bool sortinrev(const pair<T, T>&a, const pair <T, T> &b) 
{ 
	return (a.first > b.first); 
}
template <typename T>
class Maille {
private:
	T coef;
	int deg;
public:
	template <typename...Args> Maille(int de, Args...args) :deg(de) {
		coef = T(args...);
	}
	Maille(T co, int de): deg(de), coef(co){}
	Maille() { coef = deg = 0; }
	friend ostream& operator<<(ostream& os, Maille<T> m) {
		cout << m.Coeff() << "x^" << m.Degree();
		return os;
	}
	T Coeff() { return coef; }
	int Degree() { return deg; }
	void setc(T a) { coef = a; }
	void setd(int a) { deg = a; }
};
template <typename T> void swapp(Maille<T> &a, Maille<T> &b) { 
	T temp; 
	temp = b.Coeff(); 
	b.setc(a.Coeff()); 
	a.setc(temp); 
	temp = b.Degree(); 
	b.setd(a.Degree()); 
	a.setd(temp); 
}
template <typename T> class KPolynomial
{
private: 
	vector<Maille<T>> maille;
	KPolynomial(T coef) {
		cout << "В конструкторе нечётное количество элементов! Многочлен будет обнулён"<<endl;
		maille.clear();
	}
	void ToConstruct(T coef) {
		cout << "Нечетное число аргументов в конструкторе!!! Многочлен обнулён" << endl;
	}
	void ToConstruct(T coef, int degree) {
		maille.emplace_back(coef, degree);
	}
	template <typename...Args> void ToConstruct(T coef, int degree, Args...args) {
		maille.emplace_back(coef, degree);
		ToConstruct(args...);
	}
public:
	KPolynomial(){}
	KPolynomial(vector<T> &co, vector<int> &de) {
		maille.resize(co.size());
		if (co.size() == de.size()) {
			for (size_t i = 0; i < co.size(); i++) { 
				maille[i].setc(co[i]); maille[i].setd(de[i]);
			}
		}
		else 
			cout << "Количество коэффициентов и степеней не совпадают!!!";
	}
	KPolynomial(T co, int deg) {
		maille.emplace_back(co, deg);
	}
	template <typename...Args> KPolynomial(Args...args) {
		ToConstruct(args...);
		std::sort(maille.begin(), maille.end(), [](Maille<T> &comp1, Maille<T> &comp2) {return comp1.Degree() > comp2.Degree() ? true : false; });
	}

	KPolynomial(const KPolynomial<T> &r) {
		maille.assign(r.maille.begin(),r.maille.end());
	}
	KPolynomial(KPolynomial<T> &&r) {
		maille = move(r.maille);
	}
	size_t Count() {
		return maille.size();
	}
	int Degree() {
		if (!maille.empty())
			return maille[0].deg;
		else
			return -1;
	}
	void Clear() {
		size_t i = 0;
		while (i != maille.size()) {
			maille[i].setc(0);
			maille[i].setd(0);
			i++;
		};
	}
	static void Swap(KPolynomial<T> &a, KPolynomial<T> &b) {
		size_t sizea = a.maille.size(), sizeb = b.maille.size();
		bool agreater;
		size_t tsize;
		if (sizea < sizeb) { 
			agreater = false; 
			tsize = sizea; 
			a.maille.resize(sizeb); 
		}
		else { 
			agreater = true; 
			tsize = sizeb; 
			b.maille.resize(sizea); 
		}
		for (size_t i = 0; i < sizea; i++) {
			swapp(a.maille[i], b.maille[i]);
		}
		if (agreater) 
			a.maille.resize(tsize); 
		else 
			b.maille.resize(tsize);
	}

	KPolynomial<T>& operator=(KPolynomial<T> &a) {
		size_t sizef = this->maille.size(), sizes = a.maille.size();
		if (sizef < sizes) 
			this->maille.resize(sizes);
		for (size_t i = 0; i < sizes; i++) {
			this->maille[i].setd(a.maille[i].Degree());
			this->maille[i].setc(a.maille[i].Coeff());
		}
		if (sizef > sizes) 
			this->maille.resize(sizes);
		return *this;
	}
	KPolynomial<T>& operator=(KPolynomial<T> &&a) {
		this->maille = move(a.maille);
		return *this;
	}

	bool operator==(KPolynomial<T> b) {
		if (this->maille.size() != b.maille.size()) 
			return false;
		for (size_t i = 0; i < this->maille.size(); i++) {
			if ((this->maille[i].Degree() != b.maille[i].Degree()) || (this->maille[i].Coeff() != b.maille[i].Coeff())) 
				return false;
		}
		return true;
	}
	bool operator !=(KPolynomial<T> b) {
		if (this->maille.size() != b.maille.size()) 
			return true;
		for (size_t i = 0; i < this->maille.size(); i++) {
			if ((this->maille[i].Degree() != b.maille[i].Degree()) || (this->maille[i].Coeff() != b.maille[i].Coeff())) 
				return true;
		}
		return false;
	}

	friend ostream& operator<<(ostream& os, KPolynomial<T> &p) {
		if (p.maille.size() == 0) { 
			os << 0; 
			return os;
		}
		size_t n = 0;
		while ((n < p.maille.size()) && (p.maille[n].Coeff() == 0)) {
			n++;
			if (n == p.maille.size()) { 
				os << 0; 
				return os; 
			}
		}
		if (p.maille[n].Degree() == 0)
			os << p.maille[n].Coeff();
		else
			os << p.maille[n].Coeff() << "x^" << p.maille[n].Degree();
		for (size_t i = n + 1; i < p.maille.size(); i++) {
			if (p.maille[i].Degree() == 0)
				os << "+" << p.maille[i].Coeff();
			else 
				if (p.maille[i].Coeff() > 0) 
					os << "+" << p.maille[i].Coeff() << "x^" << p.maille[i].Degree();
				else if (p.maille[i].Coeff() < 0) 
					os << "-" << -p.maille[i].Coeff() << "x^" << p.maille[i].Degree();
				else 
					continue;
		}
		return os;
	}
	friend istream& operator>>(istream& is, KPolynomial<T>& b) {
		vector<T> c; vector<int> d; string str, temp;
		cin >> str;
		bool plus = true;
		auto it = str.begin();
	start:
		if (*it == '-')
			plus = false;
		else
			plus = true;
		//для -.x^.+... тоже работает
		try {
			while (*it != 'x') {
				if ((*it < '0') || (*it > '9'))
					throw 1;//"Неверно введён коэффициент, этот одночлен не будет учитываться
				temp.push_back(*it);
				++it;
				if (it == str.end())
					throw 2;//"Конец строки"
			}
		}
		catch (int i) {
			switch (i) {
			case 1:
				cout << "Неверно введён коэфициент, одночлен с неправильным коэфициентом не будет учитываться";
				while ((*it != '+') && (*it != '-')) {
					++it;
					if (it == str.end())//был введён один одночлен
						goto construct;
				}
			case 2:
				if (!temp.empty())//например для ...+5
				{
					c.push_back(stol(temp));
					d.push_back(0);
				}
				goto construct;
			}
		}
		c.push_back(stoi(temp));
		temp.clear();
		++it;//it is now supposed to be '^'
		if ((it==str.end())||(*it != '^'))//..+2x+...
			d.push_back(1);
		else
		{
			++it;
			try {
				if (it == str.end())
					throw 2;//"Конец строки" для случая ...+..x^
				while ((*it != '+')&&(*it != '-')) {
					if ((*it < '0') || (*it > '9'))
						throw 1;//"Неверно введена степень, этот одночлен не будет учитываться
					temp.push_back(*it);
					++it;
					if (it == str.end())
						throw 2;//"Конец строки"
				}
			}
			catch (int i) {
				switch (i) {
				case 1:
					cout << "Неверно введена степень, одночлен с неправильным коэфициентом не будет учитываться";
					c.erase(c.end() - 1);//удаление ячейки с коэф без соответствующей степени
					while ((*it != '+') && (*it != '-')) {//чтобы не учитывать этот одночлен
						++it;
						if (it == str.end())//был введён один одночлен
							goto construct;
					}
				case 2:
					if (!temp.empty())//например для ...+2x^2
					{
						d.push_back(stol(temp));
					}
					goto construct;
				}
			}
			d.push_back(stoi(temp));
			temp.clear();
			goto start;//ввод следующего одночлена
		}
		construct:
		b = KPolynomial<T>(c, d);
		return is;
	}

	KPolynomial<T> operator+(KPolynomial<T> a) {
		int counter = 0;
		vector<Maille<T>> mapa;
		for (size_t i = 0; i < this->maille.size(); i++) {
			mapa.emplace_back(this->maille[i].Coeff(), this->maille[i].Degree());
		}
		bool effectued = false;
		for (size_t i = 0; i < a.maille.size(); i++) {
			for (size_t j = 0; j < mapa.size(); j++) {
				if (a.maille[i].Degree() == mapa[j].Degree()) {
					mapa[j].setc(mapa[j].Coeff() + a.maille[i].Coeff()); 
					if (mapa[j].Coeff() == 0)counter++; 
					effectued = true; 
				}
			}
			if (!effectued) 
				mapa.emplace_back(a.maille[i].Coeff(), a.maille[i].Degree());
		}
		KPolynomial<T> b;
		b.maille.resize(mapa.size() - counter);
		for (size_t i = 0; i < b.maille.size(); i++) {
			if (mapa[i].Coeff() == 0) continue;
			b.maille[i].setd(mapa[i].Degree());
			b.maille[i].setc(mapa[i].Coeff());
		}
		return b;
	}
	template <typename...Args>
	void EmplaceBack(int degree, Args...args){
		maille.emplace_back(degree, args...);
		std::sort(maille.begin(), maille.end(), [](Maille<T> first, Maille<T> second) {return first.Degree() > second.Degree(); });
	}
	Maille<T>& operator[](const int &index) const{
		return maille[index];
	}
	KPolynomial<T>& operator+=(KPolynomial<T> &b) { *this = *this + b; return *this; }

	KPolynomial<T> operator-(KPolynomial<T> a) {
		int counter = 0;
		bool subd = false;
		vector<pair<int, T>> mapa;
		for (size_t i = 0; i < this->maille.size(); i++) {
			mapa.push_back({ this->maille[i].Degree(), this->maille[i].Coeff() });
		}
		int k = 0;
		for (size_t j = 0; j < a.maille.size(); j++) {
			for (size_t i = 0; i < mapa.size(); i++) {
				if (mapa[i].first == a.maille[j].Degree()) {
					mapa[i].second = mapa[i].second - a.maille[j].Coeff();
					if (mapa[i].second == 0)mapa.erase(mapa.begin() + i, mapa.begin() + i + 1);
					subd = true;
				}
			}
			if (!subd) { mapa.push_back({ a.maille[j].Degree(),a.maille[j].Coeff() }); }
		}
		sort(mapa.begin(), mapa.end(), sortinrev<T>);
		vector<int> d;
		vector<T> c;
		for (size_t i = 0; i < mapa.size(); i++) {
			d.push_back(mapa[i].first); c.push_back(mapa[i].second);
		}
		KPolynomial<T> b(c, d);
		return b;
	}

	KPolynomial<T>& operator-=(KPolynomial<T> &b) { *this = *this - b; return *this; }

	KPolynomial<T> operator*(KPolynomial<T> a) {
		vector<T> co;
		vector<int> de;
		vector<pair<int, T>> items;
		for (size_t i = 0; i < this->maille.size(); i++) {
			for (size_t j = 0; j < a.maille.size(); j++) {
				int tdegree = this->maille[i].Degree() + a.maille[j].Degree();
				int tcoeff = this->maille[i].Coeff() * a.maille[j].Coeff();
				bool found = false;
				for (size_t i = 0; i < items.size(); i++) {
					if (items[i].first == tdegree) {
						items[i].second += tcoeff;
						found = true;
						break;
					}
				}
				if (!found)items.push_back({ tdegree, tcoeff });
			}
		}
		for (size_t i = 0; i < items.size();i++) {
			de.push_back(items[i].first);
			co.push_back(items[i].second);
		}
		KPolynomial<T> pol(co, de);
		return pol;
	}
	void operator*=(KPolynomial<T> &b) {
		(*this) = (*this)*b;
	}
	KPolynomial<T> operator/(T &co){
		KPolynomial<T> result(*this);
		for (auto it = result.maille.begin(); it != result.maille.end(); ++it) {
			it->setc(it->Coeff()/co);
		}
		return result;
	}
	KPolynomial<T> operator/(KPolynomial<T> b){
		KPolynomial<T> temp;
		temp = *this;
		KPolynomial<T> result;
			if (temp.maille.empty())
				throw invalid_argument("Не введен первый многочлен");
			if (b.maille.empty())
				throw "Не введён второй многочлен!!!";
			if (b.maille.size() == 1)
				if(b.maille[0].Coeff() == 0)
					throw "Знаменатель = 0!!!";
			while (!temp.maille.empty()) {
				if (temp.maille[0].Degree() >= b.maille[0].Degree()) {
					if (b.maille[0].Coeff() == 0)
						throw "Деление на ноль!!!!";
					int tcoeff = temp.maille[0].Coeff() / b.maille[0].Coeff();
					int tdeg = temp.maille[0].Degree() - b.maille[0].Degree();
					KPolynomial<T> k(tcoeff, tdeg);//во сколько раз увеличивать первый многочлен
					KPolynomial<T> l = b * k;
					temp = temp - l;
					result.maille.push_back(k.maille[0]);
				}
				else break;
			}
		return result;
	}
	void operator/=(const KPolynomial<T> &a) {
		(*this) = (*this) / a;
	}
	struct iterator : public std::iterator<std::input_iterator_tag, Maille<T>>
	{
		friend class KPolynomial<T>;
	private:
		Maille<T>* p;
		int pos; 
		vector<Maille<T>> v;
		iterator(T* p_) : p(p_) {
		}
	public:
		iterator(vector<Maille<T>> v_, int pos_):v(v_), pos(pos_) {
			if (pos != v.size())
				p = &v[pos];
			else
				p = 0;
		}
		iterator(const iterator &it) :p(it.p), v(it.v), pos(it.pos) {
		}
		bool operator!=(iterator const& other) const {
			return this->pos != other.pos ? true : false;
		}
		bool operator==(iterator const& other) const {
			return this->pos == other.pos ? true : false;
		}
		typename iterator::reference operator*() const {
			return *p;
		}
		iterator& operator++() {
			if (++pos != v.size())
				p = &(v[pos]);
			else
				p = 0;
			return *this;
		}
	};
	iterator begin() { return iterator(maille, 0); }
	iterator end() { return iterator(maille, maille.size()); }

};




int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Многочлен с переменным количеством параметров\nВыведен с помощью copy: ";
	KPolynomial<int> l(1, 3, 1, 2, 5, 1, 1, 6, 1, 8);
	//cout << l << endl;
	copy(l.begin(), l.end(), ostream_iterator<Maille<int>>(cout, " "));
	cout << endl;
	for (auto x: l)
		cout << x << " ";
	cout << "\n" << endl;
	KPolynomial<KRat> krat;
	krat.EmplaceBack(1, 2, 3);
	krat.EmplaceBack(2, 3, 4);
	krat.EmplaceBack(2, 3);
	krat.EmplaceBack(2);
	cout << krat << endl;
	KPolynomial<int> init = { 1,2,3,4,5,6,7,2,9,1 };
	KPolynomial<int> c, a;
	cout << "Деление многочлена на многочлен\nВведите первый многочлен: ";
	cin >> c;
	cout << endl;
	cout << "Введите второй многочлен: ";
	cin >> a;
	KPolynomial<int> res;
	try {
		res = (c / a);
	}
	catch (invalid_argument &ex) {
		cout <<"\ninvalid argument:"<<ex.what();
	}
	catch (exception &ex) {
		cout<<"\n"<<ex.what();
	}
	cout << "Результат деления: " << res << endl;
	system("pause");
	return 0;
}