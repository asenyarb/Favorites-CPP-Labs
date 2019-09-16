#pragma once
#include <iostream>
#ifndef KRAT_H__
#define KRAT_H__
class KRat {
	int chisl;
	int znam;
public:
	KRat() :chisl(1), znam(1) {}
	KRat(int chisl, int znam):chisl(chisl), znam(znam) {}
	explicit KRat(int chisl) :chisl(chisl), znam(1) {}
	friend std::ostream& operator<<(std::ostream& os, const KRat& toout)
	{
		os << toout.chisl << "/" << toout.znam;
		return os;
	}
	bool operator==(int i) {
		return chisl == i ? true : false;
	}
	bool operator>(int i) {
		return chisl > i ? true : false;
	}
	bool operator<(int i) {
		return chisl < i ? true : false;
	}
	KRat& operator-() {
		chisl *= -1;
		return *this;
	}
};
#endif