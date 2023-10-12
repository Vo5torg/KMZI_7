#include "Elleptic_Curve.h"

#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#define CD 16

Digit g_p[CD], g_e[CD], g_s[CD], g_t[CD], g_h[CD], g_k[CD], g_d[CD], g_razn[CD], g_u[CD], g_v[CD], g_zero[CD], g_q[CD],
    g_p_1[CD]; // Константы
using namespace std;
void rev_mod(const Digit ch[], Digit res[]) // находит обратное число
{
    Digit *buffer = new Digit[CD], *step = new Digit[CD], *resTemp = new Digit[CD]{ 0 }, *v = new Digit[CD];
    Assig(ch, buffer);
    Assig(g_p, step);
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000002", v);
    Sub(step, v, step);
    resTemp[0] = 1;

    for(int i = 0; i <= 16 * CD - 1; i++) // Проходим по 256 битам числа
    {
        Digit a[CD];
        Digit current = step[(int)(i / 16)]; // Считаем текущую цифру
        if((current >> (i % 16)) & 0x0001) { // Проверяем, что текущий бит равен 1
            Mult(resTemp, buffer, a); // Умножаем результирующую переменную на значение буфера
            Assig(a, resTemp); // заносим результат в переменную res
        }
        Mult(buffer, buffer, a); // возводим значение буфера в квадрат
        Assig(a, buffer);
    }
    Assig(resTemp, res);
    delete[] resTemp;
    delete[] step;
    delete[] v;
    delete[] buffer;
};

void Add_Vey(const Digit x1[], const Digit y1[], const Digit x2[], const Digit y2[], Digit x_res[],
             Digit y_res[]) // сложение в форме Вейерштрасса
{
    Digit* lambda = new Digit[CD];
    Digit* temp = new Digit[CD];
    Digit* temp_2 = new Digit[CD];
    Sub(y2, y1, temp);
    Sub(x2, x1, temp_2);
    rev_mod(temp_2, temp_2);
    Mult(temp, temp_2, lambda); // Нашли лямбду
    Mult(lambda, lambda, temp);
    Sub(temp, x1, temp);
    Sub(temp, x2, x_res); // Нашли х
    Sub(x1, x_res, temp);
    Mult(lambda, temp, temp);
    Sub(temp, y1, y_res); // Нашли y
    delete[] lambda;
    delete[] temp;
    delete[] temp_2;
}
void Udv_Vey(const Digit x1[], const Digit y1[], Digit x_res[], Digit y_res[]) // удвоение в форме Вейерштрасса
{
    Digit* k1 = new Digit[CD];
    Digit* k2 = new Digit[CD];
    Digit* a = new Digit[CD];
    Digit* lambda = new Digit[CD];
    Digit* temp = new Digit[CD];
    Digit* temp_2 = new Digit[CD];
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000002", k1);
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000003", k2);
    StringToNumber("C2173F1513981673AF4892C23035A27CE25E2013BF95AA33B22C656F277E7335", a);
    Mult(x1, x1, temp);
    Mult(k2, temp, temp);
    Add(temp, a, temp);
    Mult(k1, y1, temp_2);
    rev_mod(temp_2, temp_2);
    Mult(temp, temp_2, lambda); // Нашли лямбду
    Mult(lambda, lambda, temp);
    Mult(k1, x1, temp_2);
    Sub(temp, temp_2, x_res); // Нашли х
    Sub(x1, x_res, temp);
    Mult(lambda, temp, temp);
    Sub(temp, y1, y_res); // Нашли y
    delete[] lambda;
    delete[] temp;
    delete[] temp_2;
    delete[] k1;
    delete[] k2;
    delete[] a;
}
void Vey_adds(const Digit x1[], const Digit y1[], const Digit x2[], const Digit y2[], Digit x_res[], Digit y_res[])
{
    if(Equal(x1, x2)) {
        Udv_Vey(x1, y1, x_res, y_res);
    } else {
        Add_Vey(x1, y1, x2, y2, x_res, y_res);
    }
}
void Edv_adds(const Digit x1[], const Digit y1[], const Digit x2[], const Digit y2[], Digit x_res[],
              Digit y_res[]) // сложение в форме Эдвардса
{
    Digit* temp = new Digit[CD];
    Digit* temp_2 = new Digit[CD];
    Digit* temp_3 = new Digit[CD];
    Mult(x1, y2, temp);
    Mult(x2, y1, temp_2);
    Add(temp, temp_2, temp);
    Mult(g_d, x1, temp_2);
    Mult(x2, temp_2, temp_2);
    Mult(y1, temp_2, temp_2);
    Mult(y2, temp_2, temp_2);
    Add(g_e, temp_2, temp_2);
    rev_mod(temp_2, temp_2);
    Mult(temp, temp_2, x_res); // Нашли x
    Mult(y1, y2, temp);
    Mult(g_e, x1, temp_2);
    Mult(temp_2, x2, temp_2);
    Sub(temp, temp_2, temp);
    Mult(g_d, x1, temp_2);
    Mult(x2, temp_2, temp_2);
    Mult(y1, temp_2, temp_2);
    Mult(y2, temp_2, temp_2);
    Sub(g_e, temp_2, temp_2);
    rev_mod(temp_2, temp_2);
    Mult(temp, temp_2, y_res); // Нашли y
    delete[] temp;
    delete[] temp_2;
    delete[] temp_3;
}
void get_u(Digit x[], Digit y[], Digit t[], Digit x_res[]) // получить x в форме Вейерштрасса
{
    Digit* temp = new Digit[CD];
    Sub(x, t, x_res);
    rev_mod(y, temp);
    Mult(x_res, temp, x_res);
    delete[] temp;
}
void get_v(Digit x[], Digit y[], Digit t[], Digit y_res[]) // получить y в форме Вейерштрасса
{
    Digit* temp = new Digit[CD];
    Sub(x, t, y_res);
    Add(y_res, g_s, temp);
    Sub(y_res, g_s, y_res);
    rev_mod(temp, temp);
    Mult(y_res, temp, y_res);
    delete[] temp;
}
void get_x(Digit u[], Digit v[], Digit t[], Digit x_res[]) // получить x в форме Эдвардса
{
    Digit* temp = new Digit[CD];
    Add(g_e, v, temp);
    Mult(temp, g_s, temp);
    Sub(g_e, v, x_res);
    rev_mod(x_res, x_res);
    Mult(temp, x_res, x_res);
    Add(x_res, g_t, x_res);
}
void get_y(Digit u[], Digit v[], Digit t[], Digit y_res[]) // получить y в форме Эдвардса
{
    Digit* temp = new Digit[CD];
    Add(g_e, v, temp);
    Mult(temp, g_s, temp);
    Sub(g_e, v, y_res);
    Mult(y_res, u, y_res);
    rev_mod(y_res, y_res);
    Mult(temp, y_res, y_res);
}
void VeyToEdv(Digit x[], Digit y[], Digit x_res[], Digit y_res[]) // из Вейерштрасса в Эдвардса
{
    get_u(x, y, g_t, x_res);
    get_v(x, y, g_t, y_res);
}
void EdvToVey(Digit u[], Digit v[], Digit x_res[], Digit y_res[]) // из Эдвардса в Вейерштрасса
{
    get_x(u, v, g_t, x_res);
    get_y(u, v, g_t, y_res);
}
void Print_Message(Digit x[], Digit y[], int variable, int EdvVey, int num_var) // вывод сообщений
{
    string var, string_var;
    switch(variable) {
    case 1:
        var = "A";
        break;
    case 2:
        var = "B";
        break;
    case 3:
        var = "C";
        break;
    case 4:
        var = "D";
        break;
    case 5:
        var = "K";
        break;
    }
    switch(EdvVey) {
    case 1:
        string_var = "Эдвардса";
        break;
    case 2:
        string_var = "Вейерштрасса";
        break;
    }
    if(variable == 5) {
        cout << "Число К" << num_var << ":" << endl << NumToStringDigit(x) << endl << endl;
    } else {
        cout << "Точка " << var << num_var << " на кривой в форме " << string_var << ":" << endl
             << "x:" << NumToStringDigit(x) << endl
             << "y:" << NumToStringDigit(y) << endl;
        cout << endl;
    }
}
void Mult_Vey(Digit x[], Digit y[], const Digit k[], Digit x_res[], Digit y_res[])
{
    Digit *c1 = new Digit[CD], *c2 = new Digit[CD], *x1 = new Digit[CD], *y1 = new Digit[CD];
    Assig(g_zero, x_res);
    Assig(g_zero, y_res);
    Assig(x, x1);
    Assig(y, y1);

    for(int i = 0; i <= 16 * CD - 1; i++) // Проходим по 256 битам числа
    {
        Digit current = k[(int)(i / 16)];    // Вычисляем текущую цифру
        if((current >> (i % 16)) & 0x0001) { // Проверяем, что
            // текущий бит числа равен 1
            // если в результате ещё ничего нет, то заносим значения из  буфера
            if(Equal(x_res, g_zero) && Equal(y_res, g_zero)) {
                Assig(x1, x_res);
                Assig(y1, y_res);
            }
            // если в результате значение есть, то складываем с буфером
            else {
                Add_Vey(x_res, y_res, x1, y1, c1, c2);
                Assig(c1, x_res);
                Assig(c2, y_res);
            }
        }
        // удваиваем точку
        Udv_Vey(x1, y1, c1, c2);
        Assig(c1, x1);
        Assig(c2, y1);
    }
    delete[] x1;
    delete[] y1;
    delete[] c1;
    delete[] c2;
}
void Mult_Edv(const Digit x[], const Digit y[], const Digit k[], Digit x_res[], Digit y_res[])
{
    Digit *c1 = new Digit[CD], *c2 = new Digit[CD], *x1 = new Digit[CD], *y1 = new Digit[CD];
    Assig(g_zero, x_res);
    Assig(g_e, y_res);
    Assig(x, x1);
    Assig(y, y1);

    for(int i = 0; i <= 16 * CD - 1; i++) // Проходим по 256 битам числа
    {
        Digit current = k[(int)(i / 16)];    // Вычисляем текущую цифру
        if((current >> (i % 16)) & 0x0001) { // Проверяем, что
                                             // текущий бит числа равен 1
            // если в результате ещё ничего нет, то заносим значения из  буфера
            Edv_adds(x_res, y_res, x1, y1, c1, c2);
            Assig(c1, x_res);
            Assig(c2, y_res);
        }
        // удваиваем точку
        Edv_adds(x1, y1, x1, y1, c1, c2);
        Assig(c1, x1);
        Assig(c2, y1);
    }
    delete[] x1;
    delete[] y1;
    delete[] c1;
    delete[] c2;
}
int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    Init();
    Digit x1[CD], y1[CD], x2[CD], y2[CD], k1[CD], k2[CD], ax[CD], ay[CD], bx[CD], by[CD], k3[CD], edv_x[CD], edv_y[CD],
        x_res[CD], y_res[CD];
    StringToNumber("91e38443a5e82c0d880923425712b2bb658b9196932e02c78b2582fe742daa28", x1); // Для первого КТ
    StringToNumber("32879423ab1a0375895786c4bb46e9565fde0b5344766740af268adb32322e5c", y1);
    StringToNumber("e8c6740e58d616ca220db7da0d9c3e19b53e86e38bf3e8747774631452ec174c", k1);
    StringToNumber("1d40c1676805f9518be1fb4c7ae460d3608581e477b07c2d0e7e1e265a6b3347", x2); // Для второго КТ
    StringToNumber("8291ace380fd8832baca29613ab5626c302d13348f204d727d30897a8e1f8934", y2);
    StringToNumber("c9cbaeefaabc51147130fc6fa1adbe72140e35c5911b7d54b12beecdf5848943", k2);
    StringToNumber("3508bea1bde4908b6c2572d32da08ff7f5741780e20e0a966e0f4ea20eac30b5", ax); // Для варианта 13
    StringToNumber("45e1798bc02b54c4dabcb8233c66eb778acd6dc44b2a21b140d22b7a8a49ac8f", ay);
    StringToNumber("182f29adadafa136a9635ed9d2688245885eece8b6327cd67b87d7e099243d23", bx);
    StringToNumber("d7f1e9c9c09f80c8d201c47524095b9cd0571e969eeedd3154ba59fb7db710f7", by);
    StringToNumber("b7e2e16f9951ce2b132b6f9b947606a826db96a81895883871941d6c0a8980d1", k3);
    cout << "1) Умножение на кривой в форме Вейерштрасса" << endl;
    cout << "Контрольный тест 1:" << endl;
    Print_Message(x1, y1, 1, 2, 1);
    Print_Message(k1, k1, 5, 2, 1);
    cout << "C1 = A1 * K1 ..." << endl;
    Mult_Vey(x1, y1, k1, x_res, y_res);
    Print_Message(x_res, y_res, 3, 2, 1);
    cout << endl;
    cout << "Контрольный тест 2:" << endl;
    Print_Message(x2, y2, 1, 2, 2);
    Print_Message(k2, k2, 5, 2, 2);
    cout << "C2 = A2 * K2 ..." << endl;
    Mult_Vey(x2, y2, k2, x_res, y_res);
    Print_Message(x_res, y_res, 3, 2, 2);
    cout << endl;
    cout << "Вариант 13:" << endl;
    Print_Message(k3, k3, 5, 2, 1);
    cout << "Умножение точки A на K" << endl;
    Print_Message(ax, ay, 1, 2, 1);
    cout << "C1 = A1 * K1 ..." << endl;
    Mult_Vey(ax, ay, k3, x_res, y_res);
    Print_Message(x_res, y_res, 3, 2, 1);
    cout << endl;
    cout << "Умножение точки B на K" << endl;
    Print_Message(bx, by, 2, 2, 1);
    cout << "D1 = B1 * K1 ..." << endl;
    Mult_Vey(bx, by, k3, x_res, y_res);
    Print_Message(x_res, y_res, 4, 2, 1);
    cout << "2) Умножение на кривой в форме Эдвардса" << endl;
    cout << "Контрольный тест 1:" << endl;
    VeyToEdv(x1, y1, edv_x, edv_y);
    Print_Message(edv_x, edv_y, 1, 1, 1);
    Print_Message(k1, k1, 5, 1, 1);
    cout << "C1 = A1 * K1 ..." << endl;
    Mult_Edv(edv_x, edv_y, k1, x_res, y_res);
    Print_Message(x_res, y_res, 3, 1, 1);
    EdvToVey(x_res, y_res, edv_x, edv_y);
    Print_Message(edv_x, edv_y, 3, 2, 1);
    cout << endl;
    cout << "Контрольный тест 2:" << endl;
    VeyToEdv(x2, y2, edv_x, edv_y);
    Print_Message(edv_x, edv_y, 1, 1, 2);
    Print_Message(k2, k2, 5, 1, 2);
    cout << "C2 = A2 * K2 ..." << endl;
    Mult_Edv(edv_x, edv_y, k2, x_res, y_res);
    Print_Message(x_res, y_res, 3, 1, 2);
    EdvToVey(x_res, y_res, edv_x, edv_y);
    Print_Message(edv_x, edv_y, 3, 2, 2);
    cout << endl;
    cout << "Вариант 13:" << endl;
    cout << "Умножение точки A на K" << endl;
    VeyToEdv(ax, ay, edv_x, edv_y);
    Print_Message(edv_x, edv_y, 1, 1, 1);
    Print_Message(k3, k3, 5, 1, 1);
    cout << "C1 = A1 * K1 ..." << endl;
    Mult_Edv(edv_x, edv_y, k3, x_res, y_res);
    Print_Message(x_res, y_res, 3, 1, 1);
    EdvToVey(x_res, y_res, edv_x, edv_y);
    Print_Message(edv_x, edv_y, 3, 2, 1);
    cout << endl;
    cout << "Умножение точки B на K" << endl;
    VeyToEdv(bx, by, edv_x, edv_y);
    Print_Message(edv_x, edv_y, 2, 1, 1);
    Print_Message(k3, k3, 5, 1, 1);
    cout << "D1 = B1 * K1 ..." << endl;
    Mult_Edv(edv_x, edv_y, k3, x_res, y_res);
    Print_Message(x_res, y_res, 4, 1, 1);
    EdvToVey(x_res, y_res, edv_x, edv_y);
    Print_Message(edv_x, edv_y, 4, 2, 1);
    return 0;
}