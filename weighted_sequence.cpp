/**
    Weighted Index
    Copyright (C) 2017 Carl Barton, Tomasz Kociumaka, Chang Liu, Solon P. Pissis and Jakub Radoszewski.
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <cmath>
#include <chrono>
#include <list>
#include <cstdlib>
#include <ctime>
#include <set>
#include "weighted_sequence.h"
#include "estimation.h"
#include "path.h"

using std::endl;
using std::cerr;
using get_time = std::chrono::steady_clock;

std::istream & operator >> (std::istream& input, WeightedSequence &X) {
	int N;
	input >> N;
    input >> X.alph;
    int A = X.alph.size();
    for (int i = 0; i < N; ++i) {
        double sum = 0;
        std::vector<double> symbol(A, 0);
        for (int j = 0; j < A; ++j) {
            input >> symbol[j];
            sum += symbol[j];
        }
        if (std::abs(sum-1) > EPS) {
            std::cerr << "Probabilities at position " << i << " do not sum up to 1" << std::endl;
            throw 1;
        }
        X.P.emplace_back(symbol);
    }
    return input;
}

void WeightedSequence::build_zstring(double z, bool quiet, std::ostream& result) {
    if (!quiet) {
       result << "Finished reading input. Sequence length: " << length() << endl;
        result << "Index construction started." << endl;
    }
    auto begin = get_time::now();
    
    Estimation S(*this, z);
    if (!quiet) {
        auto end = get_time::now();
        auto diff = end - begin;
        result << z << "-estimation constructed in " << chrono::duration_cast<chrono::milliseconds>(diff).count() << " milliseconds."<< endl;
//        result << z << "-estimation:" << endl << S;
        result << endl;
    }
}

PropertySuffixTree * build_index( double z, bool quiet, vector<WeightedSequence>& W, std::ostream& result )
{
	auto begin = get_time::now();
	vector<Estimation> S;
	for ( auto w : W )
	{
		Estimation s ( w, z );
		S.push_back ( s );
	}

	begin = get_time::now();
    PropertyString T;
	for ( auto est: S )
	{
	    for (PropertyString const & s : est.strings()) {
			T += s;
		}
	}
	PropertySuffixTree * WST = new PropertySuffixTree(T);
	std::vector<Path> V;
	int index = 0;
	int id = 0;
	string::const_iterator position = T.string().begin();
	for ( auto w : W )
	{
		for ( int i = 0; i < z; i++ )
		{	
			if ( T.pi(index) == int(w.length()) )
			{
				string path = T.string().substr( index, w.length() );
				WST->marking( path, id );
				if ( path == "GTAAAAGAAAAACCAA" )
					cout << "YES" << endl;

//				Path valid(position, position+w.length()-1, id);
//				V.push_back( valid );
			}
			index += w.length();
			position += w.length();
		}
		id += 1;
	}		
//	WST->EndingNodeMark( V );i
    
    if (!quiet) {
        auto end = get_time::now();
        auto diff = end - begin;
        result << "Weighted Index Constructed in " << chrono::duration_cast<chrono::milliseconds>(diff).count() << " milliseconds."<< endl;
//		result << endl << "Property Suffix Tree:" << endl << *WST;
		result << endl << "Answers to queries:" << endl;
    }
	return WST;
}

bool WeightedSequence::contains(std::string const& P) const {
    return weighted_index->contains(P);
}

vector<int> WeightedSequence::occurrences(std::string const& P) const {
    std::set<int> occs;
//	for (int o : weighted_index->occurrences(P)) {
  //      occs.insert(o);
 //   }
    return vector<int>(occs.begin(), occs.end());
}

