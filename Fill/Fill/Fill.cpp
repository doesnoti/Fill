#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void PrintField( vector < vector <int> >& field )
{
    for ( const auto thisline : field)
    {
        for ( const auto thiscolumn : thisline)
            cout << thiscolumn << " ";
        cout << endl;
    }
    cout << endl;
}

int main()
{                                   //y 0  1  2  3  4  5  6  7  8        x
    vector < vector <int> > field = { { 0, 0, 0, 3, 3, 3, 3, 3, 3 },   //0
                                      { 0, 0, 3, 1, 1, 1, 2, 2, 3 },   //1
                                      { 0, 3, 2, 2, 2, 1, 1, 3, 0 },   //2 
                                      { 3, 1, 1, 3, 2, 2, 2, 3, 0 },   //3
                                      { 3, 1, 3, 3, 2, 2, 3, 0, 0 },   //4
                                      { 0, 3, 0, 3, 2, 2, 3, 0, 0 },   //5
                                      { 0, 0, 3, 1, 2, 3, 0, 0, 0 },   //6
                                      { 0, 3, 1, 2, 2, 3, 0, 0, 0 },   //7
                                      { 0, 3, 1, 2, 3, 0, 0, 0, 0 },   //8
                                      { 0, 3, 3, 3, 3, 0, 0, 0, 0 }, };//9

    PrintField(field);

    queue<int> qxU, qyU;

    int x = 6, y = 4;               //

    qxU.push(x);
    qyU.push(y);

    int i, j;
    queue<int> qxD, qyD;
    bool flagU = false, flagD = false;
    
    while (!qxU.empty())
    {
        i = qxU.front();
        j = qyU.front();
        qxU.pop();
        qyU.pop();

        while (field[i][j - 1] != 3)
            --j;

        while (field[i][j] != 3)
        {
            field[i][j] = 0;

            if ((field[i - 1][j] != 3 && field[i - 1][j] != 0) && flagU == false)
            {
                qxU.push(i - 1);
                qyU.push(j);
                flagU == true;
            }

            if (field[i - 1][j] == 3)
                flagU == false;
            
            if ((field[i + 1][j] != 3 && field[i + 1][j] != 0) && flagD == false)
            {
                qxD.push(i + 1);
                qyD.push(j);
                flagD == true;
            }

            if (field[i + 1][j] == 3)
                flagD == false;

            ++j;
        }
    }

    while (!qxD.empty())
    {
        i = qxD.front();
        j = qyD.front();
        qxD.pop();
        qyD.pop();

        while (field[i][j - 1] != 3)
            --j;

        while (field[i][j] != 3)
        {
            field[i][j] = 0;

            if ((field[i + 1][j] != 3 && field[i + 1][j] != 0) && flagD == false)
            {
                qxD.push(i + 1);
                qyD.push(j);
                flagD == true;
            }

            if (field[i + 1][j] == 3)
                flagD == false;

            ++j;
        }
    }

    PrintField(field);
}
