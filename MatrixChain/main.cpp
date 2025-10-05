//AUTHOR: Jack Fontenot
//Assignment Title: Program 3
//Assignment Description: Matrix Chain
//Due Date: 9/21/2025
//Date Created: 9/19/2025
//Date Last Modified: 9/21/2025
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void findParenth(int** arr, int i, int j){
    if(i == j){
        cout << "A" << i+1;
        return;
    }

    cout << "(";
    int a = arr[i][j-1];
    findParenth(arr, i, a-1);
    findParenth(arr, a, j);
    cout << ")";

}

int main()
{
    int n;
    int* arr;
    int** N;
    int j;
    int** s;


    cin >> n;
    arr = new int[n+1];
    for(int i = 0; i < n+1; ++i){
        cin >> arr[i];
    }

    N = new int*[n];
    s = new int*[n];

    for(int i = 0; i < n; ++i){
        N[i] = new int[n];
        s[i] = new int[n];
    }

    for(int i = 0; i < n; ++i){
        N[i][i] = 0;
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            s[i][j] = 0;
        }
    }

    for(int i = 0; i < n; ++i){
        s[i][i] = i + 1;
    }

    for(int b = 1; b < n; ++b){
        for(int i = 0; i < n-b; ++i){
            j = i + b;
            N[i][j] += 2150000;
            for(int k = i; k < j; ++k){
                if(N[i][j] > N[k+1][j]+N[i][k]+arr[i]*arr[k+1]*arr[j+1]){
                    s[i][j-1] = k+1;
                    N[i][j] = N[k+1][j]+N[i][k]+arr[i]*arr[k+1]*arr[j+1];
                }
            }
        }
    }

    for(int i = 0; i < n; ++i){
        for(j = 0; j < i; ++j){
            N[i][j] = 0;
        }
    }

    cout << "Cost Table (m):" << endl;
    for(int i = 0; i < n; ++i){
        cout << "[";
        for(j = 0; j < n; ++j){
            cout << setw(5) << N[i][j];
            if(j != n-1){
                cout << " ,";
            }
        }
        cout << "]" << endl;
    }

    cout << endl;

    cout << "Split Table (s): " << endl;
    for(int i = 0; i < n-1; ++i){
        cout << "[";
        for(j = 0; j < n-1; ++j){
            cout << s[i][j];
            if(j != n-2){
                cout << " , ";
            }
        }
        cout << "]" << endl;
    }

    cout << endl;
    cout << "Optimal Parenthesization: ";
    findParenth(s, 0, n-1);

    cout << endl;
    cout << "Minimum number of Multiplications: " << N[0][n-1] << endl;



    return 0;
}
