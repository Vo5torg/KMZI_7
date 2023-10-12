#define _CRT_SECURE_NO_WARNINGS
#include "Elleptic_Curve.h"

#include <fstream>
#include <stdio.h>
#define CD 16

extern Digit g_p[CD], g_e[CD], g_s[CD], g_t[CD], g_h[CD], g_k[CD], g_d[CD], g_razn[CD], g_u[CD], g_v[CD], g_zero[CD],
    g_q[CD], g_p_1[CD]; // Глобальные переменные