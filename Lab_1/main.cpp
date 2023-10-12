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
struct EVCL {
    Digit a1[CD], a2[CD], a3[CD];
};

bool dlina(Digit elem[])
{
    for(int i = 0; i < CD; i++) // проходимпо цифрам
    {
        if(elem[i] != 0) {
            return false;
        } // если встретилась
    }
    return true;
}

EVCL gcd(EVCL a)
{
    if(dlina(a.a2)) {
        Assig(g_e, a.a2);
        Assig(g_zero, a.a3);
        return a;
    }
    EVCL b;
    Assig(a.a2, b.a1);
    Mod_Div(a.a1, a.a2, b.a2);
    Assig(a.a3, b.a3);
    b = gcd(b);
    EVCL c;
    Assig(b.a1, c.a1);
    Assig(b.a3, c.a2);
    Int_Div(a.a1, a.a2, c.a3);
    Mult(c.a3, b.a3, c.a3);
    Sub(b.a2, c.a3, c.a3);
    return c;
};

void rev(Digit prym[], Digit obr[])
{
    EVCL A;
    Assig(prym, A.a1);
    Assig(g_p, A.a2);
    Assig(g_p, A.a3);
    A = gcd(A);
    Assig(A.a2, obr);
};
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
int main()
{
    srand(time(NULL));        // для генерации случайных чисел
    setlocale(LC_ALL, "rus"); // работа с русским языком
    Init();                   // Инициализация глобальных переменных
    Digit **nums_input = new Digit *[5], **nums_output = new Digit *[5];
    for(int i = 0; i < 5; i++) {
        nums_input[i] = new Digit[CD];
        nums_output[i] = new Digit[CD];
    }
    StringToNumber("cb6075cd06a5a3c7aebe4ec82e65f8fa44bdb635671c8383806fb26dc5041b4c", nums_input[0]);
    StringToNumber("0d0d243259539bd1aba2736c70fc717cba7d8629928a729204deb9eb170491a2", nums_input[1]);
    StringToNumber("11f8cd98f4cf819ec83791af9bf96496c93b66d596d798f91ac80583ab7739bc", nums_input[2]);
    StringToNumber("cf2f53add6085d220892c159c612945bc25514a95afdb785deeb9e0690804a6e", nums_input[3]);
    StringToNumber("4240d8d00f0aae5b3dfa730b32004779f30dbca1d86652e23fb9d167dea4188a", nums_input[4]);
    cout << "Котрольные тесты:" << endl;
    cout << "Расширенный алгоритм Евклида:" << endl;
    for(int i = 0; i < 5; i++) {
        rev(nums_input[i], nums_output[i]);
    }
    for(int i = 0; i < 3; i++) {
        cout << NumToStringDigit(nums_output[i]) << endl;
    }
    cout << "Модулярное возведение в степень:" << endl;
    for(int i = 0; i < 5; i++) {
        rev_mod(nums_input[i], nums_output[i]);
    }
    for(int i = 0; i < 3; i++) {
        cout << NumToStringDigit(nums_output[i]) << endl;
    }
    cout << "Вариант 13 " << endl;
    cout << "Прямой элемент:" << NumToStringDigit(nums_input[3]) << endl
         << "Обратный элемент:" << NumToStringDigit(nums_output[3]) << endl;
    cout << "Прямой элемент:" << NumToStringDigit(nums_input[4]) << endl
         << "Обратный элемент:" << NumToStringDigit(nums_output[4]) << endl;

    unsigned int start_time_1 = clock();
    for(int i = 0; i < 1000; i++) {
        rev(nums_input[0], nums_output[0]);
    }
    unsigned int end_time_1 = clock();
    cout << "Время выполнения 1000 итераций расширенного алгоритма Евклида:"
         << (double)(end_time_1 - start_time_1) / CLOCKS_PER_SEC << "с" << endl;
    unsigned int start_time_2 = clock();
    for(int i = 0; i < 1000; i++) {
        rev_mod(nums_input[0], nums_output[0]);
    }
    unsigned int end_time_2 = clock();
    cout << "Время выполнения 1000 итераций модулярного возведения в степень:"
         << (double)(end_time_2 - start_time_2) / CLOCKS_PER_SEC << "с" << endl;
    for(int i = 0; i < 5; i++) {
        delete[] nums_input[i];
        delete[] nums_output[i];
    }

    return 0;
}