//
//  utilities.h
//  
//
//  Created by Hugh Khiyad on 2/15/19.
//

#ifndef MYUTILS
#define MYUTILS
#include <map>
#include <vector>
#include "typed_matrix.h"
using std::vector;
using std::string;

//Question 1
vector<double> sort_by_magnitude(vector<double> &v);

//Question 2

//Question 3
TypedMatrix<double> read_matrix_csv(const string path);

//Question 4
void write_matrix_csv(const TypedMatrix<double> &matrix, const string path);

//Question 5
std::map<string, int> occurrence_map(const string path);




#endif /* UTILITIES_H */
