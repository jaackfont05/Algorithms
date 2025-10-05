//AUTHOR: Jack Fontenot
//Assignment Title: Program 2
//Assignment Description: Maxima Set
//Due Date: 9/7/2025
//Date Created: 9/7/2025
//Date Last Modified: 9/7/2025
#include <iostream>
#include <fstream>
#include "point.h"
#include "maxima.h"
#include "graphics.h"
#include <string>
#include <utility>

using namespace std;

int main()
{

    ifstream file;
    string fName;
    Set s;
    Set maxes;
    point p;

    cin >> fName;

    file.open(fName);

    while(file >> p.x){
        file >> p.y;
        s.push(p);
    }

    file.close();

    maxes = maximaSet(s);

    cout << "Maxima Points: " << endl;
    for(int i = 0; i < maxes.Size(); ++i){
        cout << "(" << maxes.at(i).x;
        cout << ", " << maxes.at(i).y;
        cout << ")" << endl;
    }

    cout << endl;




    display(s, maxes);

    return 0;
}
