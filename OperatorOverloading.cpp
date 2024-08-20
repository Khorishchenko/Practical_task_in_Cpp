#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix
{
public:
    vector<vector<int>> a;

    Matrix() {}

    friend Matrix operator + ( const Matrix &one, const Matrix &two );
};

Matrix operator + ( const Matrix &one, const Matrix &two )
{
    Matrix result;
    result.a.resize(one.a.size(), vector<int>(one.a[0].size()));

    for (int i = 0; i < one.a.size(); i++)
    {
        for (int j = 0; j < one.a[0].size(); j++)
        {
            result.a[i][j] = one.a[i][j] + two.a[i][j];
        }
    }
    return result;
}


int main () {
   int cases;
    cin >> cases;

    for (int k = 0; k < cases; k++) {
        Matrix x, y, result;
        int n, m;
        cin >> n >> m;

        // Считывание матрицы x
        // x.a.resize(n, vector<int>(m));
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < m; j++) {
        //         cin >> x.a[i][j];
        //     }
        // }

        for (int i = 0; i < n; i++)
        {
            std::vector<int> tmp;
            int number;
            for (int j = 0; j < m; j++)
            {
                std::cin >> number;
                tmp.push_back(number);
            }
            x.a.push_back(tmp);
        }

        // Считывание матрицы y
        // y.a.resize(n, vector<int>(m));
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < m; j++) {
        //         cin >> y.a[i][j];
        //     } 
        // }

        for (int i = 0; i < n; i++)
        {
            std::vector<int> tmp;
            int number;
            for (int j = 0; j < m; j++)
            {
                std::cin >> number;
                tmp.push_back(number);
            }
            y.a.push_back(tmp);
        }


        // Сложение матриц
        result = x + y;

        // Вывод результата
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << result.a[i][j] << " ";
            }
            cout << endl;
        }
    }

   return 0;
}