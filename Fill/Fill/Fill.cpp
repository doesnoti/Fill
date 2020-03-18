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

int main()                          //Наше поле "цветов" ("3" - граница; "1, 2" - другие цвета; "0" - цвет заливки;)
{                                   //y 0  1  2  3  4  5  6  7  8  9        x
    vector < vector <int> > field = { { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },   //0
                                      { 3, 2, 1, 3, 2, 2, 1, 3, 1, 3 },   //1
                                      { 3, 2, 1, 3, 2, 3, 2, 3, 2, 3 },   //2 
                                      { 3, 1, 2, 3, 1, 3, 0, 3, 1, 3 },   //3
                                      { 3, 1, 1, 3, 2, 3, 0, 3, 0, 3 },   //4
                                      { 3, 2, 1, 3, 1, 3, 1, 3, 2, 3 },   //5
                                      { 3, 2, 2, 3, 1, 3, 2, 3, 2, 3 },   //6
                                      { 3, 0, 0, 0, 0, 3, 2, 3, 2, 3 },   //7
                                      { 3, 2, 2, 2, 2, 3, 1, 2, 0, 3 },   //8
                                      { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 }, };//9

    PrintField(field);

    queue<int> qxU, qyU;

    int x = 8, y = 1;                               //Начальная точка - задаём любую в пределах контура

    qxU.push(x);
    qyU.push(y);

    int i, j;
    queue<int> qxD, qyD;                            //Разделяем заливку по движениям вверх "U" и вниз "D"

    while (!qxU.empty() || !qxD.empty())
    {
        while (!qxU.empty())                        //Заливка вверх
        {
            bool flagU = false, flagD = false,      //Флаги для контролирования неровностей контура и избегания лишних действий с очередью
                flagExсeptU = false;                //флаг для фрагментов с цветом заливки
            i = qxU.front();
            j = qyU.front();
            qxU.pop();
            qyU.pop();

            while (field.at(i).at(j - 1) != 3)                          //Всегда сдвигаемся максимально влево
                --j;

            while (field.at(i).at(j) != 3)
            {
                field.at(i).at(j) = 0;

                if (field.at(i - 1).at(j) == 0)                         //Если попадается учаток цвета заливки
                {
                    int n = -1;

                    while (field.at(i + n).at(j) == 0 && field.at(i + n).at(j) != 3)
                        --n;

                    if (field.at(i + n).at(j) != 3 && flagExсeptU == false)
                    {
                        qxU.push(i + n);
                        qyU.push(j);
                        flagExсeptU = true;
                    }

                    if (field.at(i + n).at(j) == 3)                 //Если попадается неровность, то меняем флаг
                        flagExсeptU = false;
                }

                if (field.at(i - 1).at(j) != 3 && flagU == false)   //Если сверху нет контура, закрашенного цвета и флаг
                {                                                   //говорит, что это не ячейка, которая идёт подряд
                    qxU.push(i - 1);
                    qyU.push(j);
                    flagU = true;
                }

                if (field.at(i - 1).at(j) == 3)
                    flagU = false;

                ////////////////////////////////////////////////////////////

                if ((field.at(i + 1).at(j) != 3 && field.at(i + 1).at(j) != 0) && flagD == false)
                {
                    qxD.push(i + 1);
                    qyD.push(j);
                    flagD = true;
                }

                if (field.at(i + 1).at(j) == 3)
                    flagD = false;

                ++j;
            }
        }

        while (!qxD.empty())                //Заливка вниз
        {
            bool flagU = false, flagD = false,
                flagExсeptD = false;

            i = qxD.front();
            j = qyD.front();
            qxD.pop();
            qyD.pop();

            while (field.at(i).at(j - 1) != 3)
                --j;

            while (field.at(i).at(j) != 3)
            {
                field.at(i).at(j) = 0;

                if ((field.at(i - 1).at(j) != 3 && field.at(i - 1).at(j) != 0) && flagU == false)
                {
                    qxU.push(i - 1);
                    qyU.push(j);
                    flagU = true;
                }

                if (field.at(i - 1).at(j) == 3)
                    flagU = false;

                ///////////////////////////////////////////////////

                if (field.at(i + 1).at(j) == 0)
                {
                    int n = 1;

                    while (field.at(i + n).at(j) == 0 && field.at(i + n).at(j) != 3)
                        ++n;

                    if (field.at(i + n).at(j) != 3 && flagExсeptD == false)
                    {
                        qxD.push(i + n);
                        qyD.push(j);
                        flagExсeptD = true;
                    }

                    if (field.at(i + n).at(j) == 3)
                        flagExсeptD = false;
                }

                if (field.at(i + 1).at(j) != 3 && flagD == false)
                {
                    qxD.push(i + 1);
                    qyD.push(j);
                    flagD = true;
                }

                if (field.at(i + 1).at(j) == 3)
                    flagD = false;

                ++j;
            }
        }
    }

    PrintField(field);
}
