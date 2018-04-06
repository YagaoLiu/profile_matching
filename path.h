#pragma once

#include<string>
#include<vector>
#include<iostream>

using namespace std;

struct Path{
	string::const_iterator start;
	string::const_iterator end;
	int PatternID;
	Path(string::const_iterator s, string::const_iterator e, int id): start(s), end(e), PatternID(id) {}
};
