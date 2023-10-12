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
void rev_mod(const Digit ch[], Digit res[])
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
Digit* get_s()
{
    Digit* s = new Digit[CD];
    Digit* temp = new Digit[CD];
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000004", temp);
    Sub(g_e, g_d, s);
    rev_mod(temp, temp);
    Mult(s, temp, s);
    delete[] temp;
    return s;
}
Digit* get_t()
{
    Digit* t = new Digit[CD];
    Digit* temp = new Digit[CD];
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000006", temp);
    Add(g_e, g_d, t);
    rev_mod(temp, temp);
    Mult(t, temp, t);
    delete[] temp;
    return t;
}
Digit* get_u(Digit x[], Digit y[], Digit t[])
{
    Digit* temp = new Digit[CD];
    Digit* u = new Digit[CD];
    Sub(x, t, u);
    rev_mod(y, temp);
    Mult(u, temp, u);
    delete[] temp;
    return u;
}
Digit* get_v(Digit x[], Digit y[], Digit t[])
{
    Digit* v = new Digit[CD];
    Digit* temp = new Digit[CD];
    Sub(x, t, v);
    Add(v, g_s, temp);
    Sub(v, g_s, v);
    rev_mod(temp, temp);
    Mult(v, temp, v);
    delete[] temp;
    return v;
}
Digit* get_x(Digit u[], Digit v[], Digit t[])
{
    Digit* temp = new Digit[CD];
    Digit* x = new Digit[CD];
    Add(g_e, v, temp);
    Mult(temp, g_s, temp);
    Sub(g_e, v, x);
    rev_mod(x, x);
    Mult(temp, x, x);
    Add(x, g_t, x);
    return x;
}
Digit* get_y(Digit u[], Digit v[], Digit t[])
{
    Digit* temp = new Digit[CD];
    Digit* y = new Digit[CD];
    Add(g_e, v, temp);
    Mult(temp, g_s, temp);
    Sub(g_e, v, y);
    Mult(y, u, y);
    rev_mod(y, y);
    Mult(temp, y, y);
    return y;
}
void VeyToEdv(Digit x[], Digit y[])
{
    Digit* u = get_u(x, y, g_t);
    Digit* v = get_v(x, y, g_t);
    cout << "u: " << NumToStringDigit(u) << endl << "v: " << NumToStringDigit(v) << endl;
    delete[] u;
    delete[] v;
}
void EdvToVey(Digit u[], Digit v[])
{
    Digit* x = get_x(u, v, g_t);
    Digit* y = get_y(u, v, g_t);
    cout << "x: " << NumToStringDigit(x) << endl << "y: " << NumToStringDigit(y) << endl;
    delete[] x;
    delete[] y;
}
void health_check()
{
    Digit* s = get_s();
    Digit* t = get_t();
    if(Equal(s, g_s)) {
        cout << "\"s\" равен \"q_s\"" << endl;
    }
    if(Equal(t, g_t)) {
        cout << "\"t\" равен \"q_t\"" << endl;
    }
    delete[] s;
    delete[] t;
}
int main()
{
    srand(time(NULL));        // для генерации случайных чисел
    setlocale(LC_ALL, "rus"); // работа с русским языком
    Init();                   // Инициализация глобальных переменных
    Digit x[CD], y[CD], u[CD], v[CD];
    Digit x_1[CD], y_1[CD], x_2[CD], y_2[CD];
    Digit u_1[CD], v_1[CD], u_2[CD], v_2[CD];
    StringToNumber("91E38443A5E82C0D880923425712B2BB658B9196932E02C78B2582FE742DAA28", x);
    StringToNumber("32879423AB1A0375895786C4BB46E9565FDE0B5344766740AF268ADB32322E5C", y);
    StringToNumber("000000000000000000000000000000000000000000000000000000000000000d", u);
    StringToNumber("60ca1e32aa475b348488c38fab07649ce7ef8dbe87f22e81f92b2592dba300e7", v);
    StringToNumber("43e52883e2331cc8b94e16b6f4a78464ebeb0592a510860c85309a53844e48cd", x_1);
    StringToNumber("a06d100ce3e672dec6545d010350aa1f6b35a11beed6a92f2a021be374ab5b11", y_1);
    StringToNumber("3e3273ca78be142ad0b4daede0ec790273c9b3584f51d57a3a5b7e8a540d0bb7", u_1);
    StringToNumber("9cfc2accb56d767c988dbfb70143dd2178d4594f887f8a3c1ae6f36130edf74c", v_1);
    StringToNumber("182f29adadafa136a9635ed9d2688245885eece8b6327cd67b87d7e099243d23", x_2);
    StringToNumber("d7f1e9c9c09f80c8d201c47524095b9cd0571e969eeedd3154ba59fb7db710f7", y_2);
    StringToNumber("633295a8d457a64f048994eb7543fd69fef097e99543ece81de50d5e5335ca44", u_2);
    StringToNumber("efc2ee278b42afd7ddab0086e0650e1745d523a574e1c77c4cc97cadb408cc32", v_2);
    health_check();
    cout << "Тест:" << endl;
    cout << "Переход от формы Вейерштрасса к форме Эдвардса" << endl;
    VeyToEdv(x, y);
    cout << "Переход от формы Эдвардса к форме Вейерштрасса" << endl;
    EdvToVey(u, v);
    cout << "Вариант 13:" << endl;
    cout << "Переход от формы Вейерштрасса к форме Эдвардса для точки А" << endl;
    VeyToEdv(x_1, y_1);
    cout << "Переход от формы Эдвардса к форме Вейерштрасса для точки А" << endl;
    EdvToVey(u_1, v_1);
    cout << "Переход от формы Вейерштрасса к форме Эдвардса для точки Б" << endl;
    VeyToEdv(x_2, y_2);
    cout << "Переход от формы Эдвардса к форме Вейерштрасса для точки Б" << endl;
    EdvToVey(u_2, v_2);
    return 0;
}