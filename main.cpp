/**
 *    Weighted Index
 *    Copyright (C) 2017 Carl Barton, Tomasz Kociumaka, Chang Liu, Solon P. Pissis and Jakub Radoszewski.
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <chrono>
#include <ctime>

#include "input.h"
#include "weighted_sequence.h"

using namespace std;
using std::cerr;
using get_time = std::chrono::steady_clock;

int main (int argc, char ** argv ) {
    Settings st = decode_switches(argc, argv);
#if 0
    istream& text = st.text.is_open()?st.text:cin;
    istream& patterns = st.patterns.is_open()?st.patterns:cin;
    ostream& output = st.output.is_open()?st.output:cout;
#endif
	ifstream text ( st.text );
	ifstream patterns ( st.patterns );
	ofstream output ( st.output );
   
	int PatternNumber;
	text >> PatternNumber; 	
    vector<WeightedSequence> W;
	vector<int> length;
	W.reserve ( PatternNumber );
	for ( int i = 0; i < PatternNumber; i++ )
	{
		string PatternFile;
		text >> PatternFile;
		ifstream pattern( PatternFile );
		WeightedSequence w;
	    pattern >> w;
	    W.push_back(w);
		pattern.close();
	}
	PropertySuffixTree * WST = build_index(st.z, st.quiet, W, output);
/*
	while ( true )  {
		string pattern;
		if (!(patterns >> pattern)) break;
		output << pattern << ": ";
		if (!w.contains(pattern)) {
			output << "Not found\n";
		}
		else {
			for (auto p : w.occurrences(pattern)) {
				output << p << " ";
			}
			output << endl;
		}
	}
	*/
	    auto begin = get_time::now();
	while ( true ) {
		string pattern;
		if ( !(patterns>>pattern) ) break;
		vector<vector<int>> Occ = WST->occurrences(pattern, PatternNumber);
		for ( int i = 0; i < PatternNumber; i++ ){
			if ( Occ[i].empty() ){
				output << "pattern " << i << " not found\n";
			}
			else{
				output << i << ": ";
				for ( auto p : Occ[i] ){
					output << p << " ";
				}
				output << endl;
			}
		}
	}
	output << endl;
	output.close();
    auto end = get_time::now();
	auto diff = end - begin;
	cout<< chrono::duration_cast<chrono::milliseconds>(diff).count() << " milliseconds."<< endl;
	return 0;
}

