//
//  utilities.c
//  
//
//  Created by Hugh Khiyad on 2/15/19.
//

#include "utilities.h"
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "typed_matrix.h"
#include <map>
#include <cstring>

using namespace std;

//Question 1
vector<double> sort_by_magnitude(vector<double> &v) {

    sort(v.begin(), v.end(), [](double &a, double &b) {
        return abs(a) < abs(b);
    });
    return v;
}


//Question 5
std::map<string, int> occurrence_map(const string path){

    ifstream file;
    file.open(path);

    if (!file.is_open()) cerr << "Can't open input file!";

    //vector<string> v(istream_iterator<string>(file), {});
    map<string, int> a;
    //int count = 0;
    string line = "";

    while(getline(file, line)) {

        string cell;
        istringstream ss(line);
        string word;
        while(getline(ss, cell, ' ')){
            //remove punt at end
            int end =cell.size()-1;
            if(cell[end] ==',' ||cell[end] =='-'||cell[end] =='.'||cell[end] ==')'||cell[end] =='\"'||cell[end] ==':') {
                cell.erase(end, 1);
            }
            //remove punt at second end if need
            int end2 = cell.size()-1;
            if(cell[end2] =='.') {
                cell.erase(end2, 1);
            }
            //remove punt at begin
            if(cell[0] =='('||cell[0] =='\"'){
                cell.erase(0, 1);
            }
            word = cell;
            //all to lower case
            for(char &c:word){
                c= tolower(c);
            }


            if(a.find(word)==a.end()){
                a[word]=1;
            } else{
                a[word]++;
            }

        }


    }


    file.close();

    for(auto i = a.begin(); i != a.end(); i++) {
        string key = i->first;
        //int index = 0;
        //string remove;

        size_t pos = key.find_first_of("_)(*&^%$$#@!~`<>./?:\"{}[]");
        if (pos != -1) {
            // invalid
            //cout<<key<<endl;
            a.erase(key);

        }

    }
    return a;

}


//Question 3
TypedMatrix<double> read_matrix_csv(const string path) {
    //check invalid csv

    //check csv does not exit

    ifstream file;

    file.open(path);
    if (!file.is_open()) {
        throw std::range_error("file does not exist");
    }


    vector <vector<double> > dataList;
    int row = 0;
    string line;

    while (getline(file, line)) {
        vector<double> temp;
        string cell;
        double number;
        istringstream ss(line);
        while(getline(ss, cell, ',')){
            //check content is valid or not
            int k=0;
            while (k<cell.size()) {

                if(isalpha(cell[k])){

                    throw std::range_error("invalid csv file");

                } else {
                    k++;
                }

            }

            number = atof(cell.c_str());
            temp.push_back(number);
        }
        dataList.push_back(temp);
        row++;
    }
    file.close();

    TypedMatrix<double> m(dataList[0].size(), row);

    for (int i = 0; i< row; i++) {
        for (int j = 0; j< dataList[i].size(); j++) {

            double value = dataList[i][j];
            m.set(i, j, value);
        }
    }
    return m;

}


//Question 4
void write_matrix_csv(const TypedMatrix<double> &matrix, const string path) {
    ofstream myfile;
    myfile.open(path);

    //string mystr;
    for (int i = 0; i < matrix.row_size(); i++) {
        for (int j = 0; j < matrix.column_size(); j++) {
            double value = matrix.get(i,j);
            string str = to_string(value);
            //mystr += str;
            myfile<<str;
            if (j < matrix.column_size()-1 ) {
                myfile<< ", ";
            }
        }
        myfile<<endl;
    }
    myfile.close();
    return;
}



