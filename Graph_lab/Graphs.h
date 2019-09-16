#pragma once
#include "stdafx.h"
#ifndef GRAPHS_H__
#define GRAPHS_H__
class Vertex
{
	
public:
	friend std::ostream& operator<<(std::ostream &os, Vertex const &v) {
		os << "{ " << v.numb << ", " << v.val << " }";
		return os;
	}
	friend std::istream& operator>>(std::istream &is, Vertex &v) {
		is >> v.numb;
		is >> v.val;
		return is;
	}
	int numb;
	int val;
};
class Edge
{
public: 
	friend std::ostream& operator<<(std::ostream& os, Edge const &e) {
		os << "{ " << e.begin << ", " << e.end << ", " << e.weight << " }";
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Edge &e) {
		is >> e.begin >> e.end >> e.weight;
		return is;
	}
	int begin;
	int end;
	int weight;
};
#endif