#include "stdafx.h"
#include<map>
#include <iostream>
#include<algorithm>
#include<iterator>
#include<list>
#include <fstream>
#include <vector>
#include<set>
int main()
{
	std::vector<Edge> ve;
	std::vector<Vertex> vv;
	typedef std::istream_iterator<Vertex> is_iterVert;
	typedef std::istream_iterator<Edge>   is_iterKEdge;

	typedef std::vector<Edge>::iterator iterator;


	std::ifstream fi("inv.txt");
	std::ofstream fo("outv.txt");
	if (fi)
	{
		copy(is_iterVert(fi), is_iterVert(), back_inserter(vv));
		fo << "List of vertices: ";
		copy(vv.begin(), vv.end(), std::ostream_iterator<Vertex>(fo, " "));
	}
	else
		std::cout << "Couldn't open inv.txt";
	fo << std::endl;

	std::ifstream fi_e("ine.txt");
	if (fi_e)
	{
		copy(is_iterKEdge(fi_e), is_iterKEdge(), back_inserter(ve));
		fo << "List of edges: ";
		copy(ve.begin(), ve.end(), std::ostream_iterator<Edge>(fo, " "));
	}
	else
		std::cout << "Couldn't open ine.txt";
	fo << std::endl;


	std::map<int, std::set<int>> m;

	std::for_each(ve.begin(), ve.end(), [&m](Edge const &e) {m[e.end].insert(e.begin); });
	std::list<int> result;
	std::for_each(vv.begin(), vv.end(), [&result, &m](Vertex const& v) {
		if (std::find_if(m.begin(), m.end(), [v](std::pair<int, std::set<int>> const& p) {return p.first == v.numb; }) == m.end())
			result.push_back(v.numb);
	});
	fo << "Vertices, not included by any edge: ";
	copy(result.begin(), result.end(), std::ostream_iterator<int>(fo, " "));
	
	return 0;
}