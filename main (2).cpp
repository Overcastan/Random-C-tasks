#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

class RationalDivisionByZero {
};

class Rational {
	int p;
	int q;
	void reduce() {
		if (p != 0) {
			int ptemp = p;
			int qtemp = q;
			while (qtemp) {
				int temp = qtemp;
				qtemp = ptemp % qtemp;
				ptemp = temp;
			}
			p /= ptemp;
			q /= ptemp;
		} else {
			q = 1;
		}
		if (q < 0) {
			q = -q;
			p = -p;
		}
	}
public:
	Rational() : p(0), q(1) {}
	Rational(int p) : p(p), q(1) {}
	Rational(int p, int q) : p(p), q(q) {
		reduce();
	}
	int getNumerator() const {
		return p;
	}
	int getDenominator() const {
		return q;
	}
	friend std::ostream& operator<<(std::ostream &os, Rational obj) {
		obj.reduce();
		if (obj.p == 0 || obj.q == 1) {
			os << obj.p;
		} else {
			os << obj.p << "/" << obj.q;
		}
		return os;
	}
	friend std::istream& operator>>(std::istream &is, Rational &obj) {
		is >> obj.p;
		if (is.peek() == '/') {
			is.ignore();
			is >> obj.q;
		}
		return is;
	}
	Rational& operator=(const Rational&);
	friend Rational operator/(int, const Rational&);
	Rational operator/(const Rational&) const;
	bool operator<(const Rational&) const;
	bool operator<=(const Rational&) const;
	bool operator>(const Rational&) const;
	bool operator>=(const Rational&) const;
	bool operator==(const Rational&) const;
	bool operator!=(const Rational&) const;
	bool operator<(int) const;
	bool operator<=(int) const;
	bool operator>(int) const;
	bool operator>=(int) const;
	bool operator==(int) const;
	bool operator!=(int) const;
	friend bool operator<(int&, const Rational&);
	friend bool operator<=(int&, const Rational&);
	friend bool operator>(int&, const Rational&);
	friend bool operator>=(int&, const Rational&);
	friend bool operator==(int&, const Rational&);
	friend bool operator!=(int&, const Rational&);
	friend Rational operator+(int, const Rational&);
	Rational operator+(int) const;
	Rational operator*(int) const;
	Rational operator-() const;
	Rational operator+() const;
	Rational operator*(const Rational&) const;
	Rational operator-(const Rational&) const;
	Rational& operator++();
	Rational operator++(int);
	Rational& operator--();
	Rational operator--(int);
	Rational& operator+=(const Rational&);
	Rational& operator-=(const Rational&);
	Rational& operator/=(const Rational&);
	Rational& operator*=(int);
	Rational& operator/=(int);
};

Rational& Rational::operator=(const Rational& other) {
	p = other.p;
	q = other.q;
	reduce();
	return *this;
}

Rational operator/(int x, const Rational& obj) {
	if (obj.p == 0) {
		throw RationalDivisionByZero();
	} else {
		Rational result;
		result.p = x * obj.q;
		result.q = obj.p;
		result.reduce();
		return result;
	}
}

Rational Rational::operator/(const Rational& other) const {
	if (other.p == 0) {
		throw RationalDivisionByZero();
	} else {
		Rational result;
		result.p = p * other.q;
		result.q = q * other.p;
		result.reduce();
		return result;
	}
}

bool Rational::operator==(const Rational& other) const {
	Rational first = *this;
	Rational second = other;
	first.reduce();
	second.reduce();
	if (first.p == second.p && first.q == second.q) {
		return true;
	}
	return false;
}

bool Rational::operator!=(const Rational& other) const {
	if (*this == other) {
		return false;
	}
	return true;
}

bool Rational::operator>(const Rational& other) const {
	Rational temp;
	temp.p = p * other.q - other.p * q;
	temp.q = q * other.q;
	temp.reduce();
	return temp.p > 0 ? true : false;
}

bool Rational::operator<(const Rational& other) const {
	Rational temp;
	temp.p = p * other.q - other.p * q;
	temp.q = q * other.q;
	temp.reduce();
	return temp.p < 0 ? true : false;
}

bool Rational::operator<=(const Rational& other) const {
	return !(*this > other);
}

bool Rational::operator>=(const Rational& other) const {
	return !(*this < other);
}

bool Rational::operator<(int x) const {
	Rational temp(x);
	return *this < temp;
}

bool Rational::operator>(int x) const {
	Rational temp(x);
	return *this > temp;
}

bool Rational::operator<=(int x) const {
	Rational temp(x);
	return *this <= temp;
}

bool Rational::operator>=(int x) const {
	Rational temp(x);
	return *this >= temp;
}

bool Rational::operator==(int x) const {
	Rational temp(x);
	return *this == temp;
}

bool Rational::operator!=(int x) const {
	Rational temp(x);
	return *this != temp;
}

bool operator<(int& x, const Rational& obj) {
	return obj > x;
}

bool operator>(int& x, const Rational& obj) {
	return obj < x;
}

bool operator<=(int& x, const Rational& obj) {
	return !(obj < x);
}

bool operator>=(int& x, const Rational& obj) {
	return !(obj > x);
}

bool operator==(int& x, const Rational& obj) {
	return obj == x;
}

bool operator!=(int& x, const Rational& obj) {
	return obj != x;
}

Rational operator+(int x, const Rational& obj) {
	Rational result(x);
	result.p = x * obj.q + obj.p;
	result.q = obj.q;
	result.reduce();
	return result;
}

Rational Rational::operator+(int x) const {
	Rational result(x + *this);
	result.reduce();
	return result;
}
Rational Rational::operator*(int x) const {
	Rational result;
	result.p = x * p;
	result.q = q;
	result.reduce();
	return result;
}

Rational Rational::operator-() const {
	Rational result;
	result.p = -p;
	result.q = q;
	return result;
}

Rational Rational::operator+() const {
	return *this;
}

Rational Rational::operator*(const Rational& other) const {
	Rational result;
	result.p = p * other.p;
	result.q = q * other.q;
	result.reduce();
	return result;
}

Rational Rational::operator-(const Rational& other) const {
	Rational result;
	result.p = p * other.q - other.p * q;
	result.q = q * other.q;
	result.reduce();
	return result;
}

Rational& Rational::operator++() {
	p += q;
	reduce();
	return *this;
}

Rational Rational::operator++(int notUsed) {
	Rational temp(*this);
	p += q;
	reduce();
	return temp;;
}

Rational& Rational::operator--() {
	p -= q;
	reduce();
	return *this;
}

Rational Rational::operator--(int notUsed) {
	Rational temp(*this);
	p -= q;
	reduce();
	return temp;;
}

Rational& Rational::operator+=(const Rational& other) {
	p = p * other.q + other.p * q;
	q = q * other.q;
	reduce();
	return *this;
}

Rational& Rational::operator-=(const Rational& other) {
	p = p * other.q - other.p * q;
	q = q * other.q;
	reduce();
	return *this;
}

Rational& Rational::operator/=(const Rational& other) {
	if (other.p == 0) {
		throw RationalDivisionByZero();
	} else {
		p = p * other.q;
		q = q * other.p;
		reduce();
		return *this;
	}
}

Rational& Rational::operator*=(int x) {
	p = p * x;
	reduce();
	return *this;
}

Rational& Rational::operator/=(int x) {
	if (x == 0) {
		throw RationalDivisionByZero();
	} else {
		q = q * x;
		reduce();
		return *this;
	}
}

int main(int argc, char** argv) {
	int a;
	cin >> a;

	int p, q;
	cin >> p >> q;
	const Rational rc(p, q); // q != 0 is guaranteed by author of tests
	cout << rc.getNumerator() << ' ' << rc.getDenominator() << endl;

	Rational r1, r2;
	cin >> r1 >> r2;

	cout << r1 << endl;
	cout << r2 << endl;

	try {
		cout << 1 / r1 << endl;
	}
	catch (const RationalDivisionByZero& ex) {
		cout << "Cannot get reciprocal of r1." << endl;
	}

	try {
		cout << rc / r2 << endl;
	}
	catch (const RationalDivisionByZero& ex) {
		cout << "Cannot divide by r2." << endl;
	}

	cout << (r1 < r2) << endl;
	cout << (r1 <= r2) << endl;
	cout << (r1 > r2) << endl;
	cout << (r1 >= r2) << endl;
	cout << (r1 == r2) << endl;
	cout << (r1 != r2) << endl;

	cout << (r1 < a) << endl;
	cout << (r1 <= a) << endl;
	cout << (r1 > a) << endl;
	cout << (r1 >= a) << endl;
	cout << (r1 == a) << endl;
	cout << (r1 != a) << endl;

	cout << (a < r2) << endl;
	cout << (a <= r2) << endl;
	cout << (a > r2) << endl;
	cout << (a >= r2) << endl;
	cout << (a == r2) << endl;
	cout << (a != r2) << endl;

	cout << rc + a << endl
		<< a + rc << endl
		<< -rc * r1 << endl
		<< (+r1 - r2 * rc) * a << endl;

	cout << ++r1 << endl;
	cout << r1 << endl;
	cout << r1++ << endl;
	cout << r1 << endl;
	cout << --r1 << endl;
	cout << r1 << endl;
	cout << r1-- << endl;
	cout << r1 << endl;
	cout << ++++r1 << endl;
	cout << r1 << endl;

	cout << ((((r1 += r2) /= Rational(-5, 3)) -= rc) *= a) << endl;
	cout << (r1 += r2 /= 3) << endl;
	cout << r1 << endl;
	cout << r2 << endl;

	return 0;
}