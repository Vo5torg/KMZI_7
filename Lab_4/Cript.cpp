#include "Cript.h"
#define CD 16

#include <iostream>
#include <math.h>
Digit hexStringToInt(string hex_pred)
{
    Digit res = 0;
    int deg;
    for(long unsigned int i = 0; i < hex_pred.size(); i++) {
        if(hex_pred[hex_pred.size() - 1 - i] >= '0' && hex_pred[hex_pred.size() - 1 - i] <= '9') {
            deg = hex_pred[hex_pred.size() - 1 - i] - '0';
            res += deg * pow(16, i);
        } else
            switch((hex_pred[hex_pred.size() - 1 - i])) {
            case('A'):
                deg = 10;
                res += deg * pow(16, i);
                break;
            case('B'):
                deg = 11;
                res += deg * pow(16, i);
                break;
            case('C'):
                deg = 12;
                res += deg * pow(16, i);
                break;
            case('D'):
                deg = 13;
                res += deg * pow(16, i);
                break;
            case('E'):
                deg = 14;
                res += deg * pow(16, i);
                break;
            case('F'):
                deg = 15;
                res += deg * pow(16, i);
                break;
            case('a'):
                deg = 10;
                res += deg * pow(16, i);
                break;
            case('b'):
                deg = 11;
                res += deg * pow(16, i);
                break;
            case('c'):
                deg = 12;
                res += deg * pow(16, i);
                break;
            case('d'):
                deg = 13;
                res += deg * pow(16, i);
                break;
            case('e'):
                deg = 14;
                res += deg * pow(16, i);
                break;
            case('f'):
                deg = 15;
                res += deg * pow(16, i);
                break;
            }
    }
    return res;
}
void StringToNumber(string str, /*Ïðåîáðàçóåìàÿ ñòðîêà*/
                    Digit Res[] /*Ïîëó÷àåìîå ÷èñëî*/
)
{
    for(int i = 0; i < CD; i++)
        Res[CD - 1 - i] = hexStringToInt(str.substr(i * 4, 4));
}
string NumToStringDigit(const Digit Numb[] /*Èíâåðòèðóåìîå ÷èñëî*/
)
{
    stringstream srt;
    for(int i = 0; i < CD; i++)
        srt << setfill('0') << setw(4) << hex << Numb[CD - 1 - i];
    return srt.str();
}
/*--------------------------------------------------------
Èíèöèàëèçàöèÿ êîíñòàíò
--------------------------------------------------------*/
void Init()
{
    StringToNumber("7e7e82520f9f015faa1d0f18c14ab9fb35188275da3fd94206b74f34a48e0ecd", g_s); // s=(e-d) / 4
    StringToNumber("0100fe73f595ff158e974b44d478d9588744fe5c192ac47ea63075dce7a14aaa", g_t); // t=(e+d) / 6
    StringToNumber("7f7f80c60535007538b45a5d95c39353bc5d80d1f36a9dc0ace7c5118c2f5977", g_h); // t+s
    StringToNumber("7d7d83de1a09024a1b85c3d3ecd1e0a2add38419c11514c36086d957bcecc423", g_k); // s-t
    StringToNumber("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD97", g_p);
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000001", g_e);
    StringToNumber("0605F6B7C183FA81578BC39CFAD518132B9DF62897009AF7E522C32D6DC7BFFB", g_d);
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000269", g_razn);
    StringToNumber("000000000000000000000000000000000000000000000000000000000000000D", g_u);
    StringToNumber("60CA1E32AA475B348488C38FAB07649CE7EF8DBE87F22E81F92B2592DBA300E7", g_v);
    StringToNumber("0000000000000000000000000000000000000000000000000000000000000000", g_zero);
    StringToNumber("400000000000000000000000000000000FD8CDDFC87B6635C115AF556C360C67", g_q);
    StringToNumber("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD96", g_p_1);
}
/*--------------------------------------------------------
Îïåðàòîðû ñðàâíåíèÿ è ïðèñâîåíèÿ
--------------------------------------------------------*/
void Assig(const Digit first[], Digit second[])
{
    for(int i = 0; i < CD; i++) {
        second[i] = first[i];
    }
}
bool Less(const Digit first[], const Digit second[])
{
    for(int i = 0; i < CD; i++) {
        if(first[CD - 1 - i] < second[CD - 1 - i])
            return true;
        if(first[CD - 1 - i] > second[CD - 1 - i])
            return false;
    }
    return false;
}
bool More(const Digit first[], const Digit second[])
{
    for(int i = 0; i < CD; i++) {
        if(first[CD - 1 - i] > second[CD - 1 - i])
            return true;
        if(first[CD - 1 - i] < second[CD - 1 - i])
            return false;
    }
    return false;
}
bool Equal(const Digit first[], const Digit second[])
{
    for(int i = 0; i < CD; i++) {
        if(first[CD - 1 - i] > second[CD - 1 - i])
            return false;
        if(first[CD - 1 - i] < second[CD - 1 - i])
            return false;
    }
    return true;
}
/*--------------------------------------------------------
Ñëîæåíèå äëèííûõ ÷èñåë (*pcf,Res) = first + second
--------------------------------------------------------*/
static void Add(Digit Res[],          /* ñóììà (size öèôð) */
                const Digit first[],  /* ïåðâîå ñëàãàåìîå (size öèôð) */
                const Digit second[], /* âòîðîå ñëàãàåìîå (size öèôð)*/
                Digit* pcf,           /* ôëàã ïåðåíîñà (1 öèôðà), ì.á. NULL */
                int size)             /* ðàçìåð ÷èñåë â öèôðàõ */
{
    TwoDigit buf; /* äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî ðåçóëüòàòà ñëîæåíèÿ */
    Digit cf = 0; /* äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî ïåðåíîñà */
    int i;        /* èäåêñíàÿ ïåðåìåííàÿ öèêëà */
    for(i = 0; i < size; i++) /* îðãàíèçàöèÿ öèêëà ïî i */
    {
        buf = (TwoDigit)first[i] + second[i] + cf; /* ñëîæåíèå i-õ öèôð è ïðåäûäóùåãî ïåðåíîñà */
        Res[i] = LODIGIT(buf);                     /* i-ÿ öèôðà Res - ìëàäøàÿ öèôðà ñóììû */
        cf = HIDIGIT(buf);                         /* ïåðåíîñ - ñòàðøàÿ öèôðà ñóììû */
    }
    if(pcf)
        *pcf = cf; /* åñëè àäðåñ pcf íå 0, âîçâðàùàåì ïåðåíîñ */
}
void Add(                      /* Ñëîæåíèå ïî ìîäóëþ p*/
         const Digit first[],  /* ïåðâîå ñëàãàåìîå (size öèôð) */
         const Digit second[], /* âòîðîå ñëàãàåìîå (size öèôð)*/
         Digit Res[]           /* ñóììà (size öèôð) */
)
{
    TwoDigit buf; /* äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî ðåçóëüòàòà ñëîæåíèÿ */
    Digit cf = 0; /* äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî ïåðåíîñà */
    int i;        /* èäåêñíàÿ ïåðåìåííàÿ öèêëà */
    for(i = 0; i < CD; i++) /* îðãàíèçàöèÿ öèêëà ïî i */
    {
        buf = (TwoDigit)first[i] + second[i] + cf; /* ñëîæåíèå i-õ öèôð è ïðåäûäóùåãî ïåðåíîñà */
        Res[i] = LODIGIT(buf);                     /* i-ÿ öèôðà Res - ìëàäøàÿ öèôðà ñóììû */
        cf = HIDIGIT(buf);                         /* ïåðåíîñ - ñòàðøàÿ öèôðà ñóììû */
    }
    if(cf != 0) {
        cf = 0;
        for(i = 0; i < CD; i++) /* îðãàíèçàöèÿ öèêëà ïî i */
        {
            buf = (TwoDigit)Res[i] + g_razn[i] + cf; /* ñëîæåíèå i-õ öèôð è ïðåäûäóùåãî ïåðåíîñà */
            Res[i] = LODIGIT(buf);                   /* i-ÿ öèôðà Res - ìëàäøàÿ öèôðà ñóììû */
            cf = HIDIGIT(buf);                       /* ïåðåíîñ - ñòàðøàÿ öèôðà ñóììû */
        }
    } /* åñëè àäðåñ pcf íå 0, âîçâðàùàåì ïåðåíîñ */
}
void Add_q(                      /* Ñëîæåíèå ïî ìîäóëþ p*/
           const Digit first[],  /* ïåðâîå ñëàãàåìîå (size öèôð) */
           const Digit second[], /* âòîðîå ñëàãàåìîå (size öèôð)*/
           Digit Res[]           /* ñóììà (size öèôð) */
)
{
    TwoDigit buf; /* äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî ðåçóëüòàòà ñëîæåíèÿ */
    Digit cf = 0; /* äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî ïåðåíîñà */
    int i;        /* èäåêñíàÿ ïåðåìåííàÿ öèêëà */
    for(i = 0; i < CD; i++) /* îðãàíèçàöèÿ öèêëà ïî i */
    {
        buf = (TwoDigit)first[i] + second[i] + cf; /* ñëîæåíèå i-õ öèôð è ïðåäûäóùåãî ïåðåíîñà */
        Res[i] = LODIGIT(buf);                     /* i-ÿ öèôðà Res - ìëàäøàÿ öèôðà ñóììû */
        cf = HIDIGIT(buf);                         /* ïåðåíîñ - ñòàðøàÿ öèôðà ñóììû */
    }
    while(More(Res, g_q)) {
        Digit* z = new Digit[CD];
        Sub(Res, g_q, z);
        Assig(z, Res);
        delete[] z;
    }
}

/*--------------------------------------------------------
Âû÷èòàíèå äëèííûõ ÷èñåë (*pcf,Res) = first - second
--------------------------------------------------------*/
static void Sub(Digit Res[],          /* ðàçíîñòü (size öèôð) */
                const Digit first[],  /* óìåíüøàåìîå (size öèôð) */
                const Digit second[], /* âû÷èòàåìîå (size öèôð) */
                Digit* pcf,           /* ôëàã çàåìà ðàçðÿäîâ (1 öèôðà), ì.á. NULL */
                int size)             /* ðàçìåð ÷èñåë â öèôðàõ */
{
    LongDigit buf; /* çíàêîâàÿ ïåðåìåííàÿ äëÿ âûäåëåíèÿ çàåìà ðàçðÿäîâ */
    Digit cf = 0;  /* äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî çàåìà */
    int i;         /* èäåêñíàÿ ïåðåìåííàÿ öèêëà */
    for(i = 0; i < size; i++) /* îðãàíèçàöèÿ öèêëà ïî i */
    {
        buf = (LongDigit)first[i] - second[i] - cf; /* âû÷èòàíèå i-õ öèôð ñ ó÷åòîì ïðåäûäóùåãî çàåìà */
        Res[i] = LODIGIT(buf); /* i-ÿ öèôðà Res - ìëàäøàÿ öèôðà ðàçíîñòè buf */
        cf = HIDIGIT(buf);     /* çàåì - ñòàðøàÿ öèôðà ðàçíîñòè buf */
        if(cf)
            cf = 1; /* åñëè çàåì áûë, ôëàãó çàåìà ïðèñâàåâàåì 1 */
    }
    if(pcf)
        *pcf = cf; /* åñëè àäðåñ pcf íå 0, âîçâðàùàåì çàåì */
}
void Sub(const Digit first[],  /* óìåíüøàåìîå (size öèôð) */
         const Digit second[], /* âû÷èòàåìîå (size öèôð) */
         Digit Res[]           /* ðàçíîñòü (size öèôð) */
)
{
    Digit Res2[CD];
    LongDigit buf; /* çíàêîâàÿ ïåðåìåííàÿ äëÿ âûäåëåíèÿ çàåìà ðàçðÿäîâ */
    Digit cf = 0;  /* äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî çàåìà */
    int i;         /* èäåêñíàÿ ïåðåìåííàÿ öèêëà */
    if(Less(first, second)) {
        for(i = 0; i < CD; i++) /* îðãàíèçàöèÿ öèêëà ïî i */
        {
            buf = (LongDigit)g_p[i] - second[i] - cf; /* âû÷èòàíèå i-õ öèôð ñ ó÷åòîì ïðåäûäóùåãî çàåìà */
            Res2[i] = LODIGIT(buf); /* i-ÿ öèôðà Res - ìëàäøàÿ öèôðà ðàçíîñòè buf */
            cf = HIDIGIT(buf);      /* çàåì - ñòàðøàÿ öèôðà ðàçíîñòè buf */
            if(cf)
                cf = 1; /* åñëè çàåì áûë, ôëàãó çàåìà ïðèñâàåâàåì 1 */
        }
        Add(first, Res2, Res);
    } else {
        for(i = 0; i < CD; i++) /* îðãàíèçàöèÿ öèêëà ïî i */
        {
            buf = (LongDigit)first[i] - second[i] - cf; /* âû÷èòàíèå i-õ öèôð ñ ó÷åòîì ïðåäûäóùåãî çàåìà */
            Res[i] = LODIGIT(buf); /* i-ÿ öèôðà Res - ìëàäøàÿ öèôðà ðàçíîñòè buf */
            cf = HIDIGIT(buf);     /* çàåì - ñòàðøàÿ öèôðà ðàçíîñòè buf */
            if(cf)
                cf = 1; /* åñëè çàåì áûë, ôëàãó çàåìà ïðèñâàåâàåì 1 */
        }
    }
}
void Sub_q(const Digit first[],  /* óìåíüøàåìîå (size öèôð) */
           const Digit second[], /* âû÷èòàåìîå (size öèôð) */
           Digit Res[]           /* ðàçíîñòü (size öèôð) */
)
{
    Digit Res2[CD];
    LongDigit buf; /* çíàêîâàÿ ïåðåìåííàÿ äëÿ âûäåëåíèÿ çàåìà ðàçðÿäîâ */
    Digit cf = 0;  /* äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî çàåìà */
    int i;         /* èäåêñíàÿ ïåðåìåííàÿ öèêëà */
    if(Less(first, second)) {
        for(i = 0; i < CD; i++) /* îðãàíèçàöèÿ öèêëà ïî i */
        {
            buf = (LongDigit)g_q[i] - second[i] - cf; /* âû÷èòàíèå i-õ öèôð ñ ó÷åòîì ïðåäûäóùåãî çàåìà */
            Res2[i] = LODIGIT(buf); /* i-ÿ öèôðà Res - ìëàäøàÿ öèôðà ðàçíîñòè buf */
            cf = HIDIGIT(buf);      /* çàåì - ñòàðøàÿ öèôðà ðàçíîñòè buf */
            if(cf)
                cf = 1; /* åñëè çàåì áûë, ôëàãó çàåìà ïðèñâàåâàåì 1 */
        }
        Add(first, Res2, Res);
    } else {
        for(i = 0; i < CD; i++) /* îðãàíèçàöèÿ öèêëà ïî i */
        {
            buf = (LongDigit)first[i] - second[i] - cf; /* âû÷èòàíèå i-õ öèôð ñ ó÷åòîì ïðåäûäóùåãî çàåìà */
            Res[i] = LODIGIT(buf); /* i-ÿ öèôðà Res - ìëàäøàÿ öèôðà ðàçíîñòè buf */
            cf = HIDIGIT(buf);     /* çàåì - ñòàðøàÿ öèôðà ðàçíîñòè buf */
            if(cf)
                cf = 1; /* åñëè çàåì áûë, ôëàãó çàåìà ïðèñâàåâàåì 1 */
        }
    }
}

/*--------------------------------------------------------
Äåëåíèå äëèííûõ ÷èñåë
--------------------------------------------------------*/

/*--------------------------------------------------------
    Îáíóëåíèå äëèííîãî ÷èñëà num = 0
--------------------------------------------------------*/
static void Zero(Digit num[], /* îáíóëÿåìîå ÷èñëî (size öèôð) */
                 int size)    /* ðàçìåð ÷èñëà â öèôðàõ */
{
    int i; /* èäåêñíàÿ ïåðåìåííàÿ öèêëà */

    for(i = 0; i < size; i++) /* îðãàíèçàöèÿ öèêëà ïî i */
        num[i] = 0;           /* îáíóëåíèå i-îé öèôðû ÷èñëà num */
}

static void Assign(Digit num1[],       /* ïîëó÷àòåëü (size öèôð) */
                   const Digit num2[], /* èñòî÷íèê (size öèôð) */
                   int size)           /* ðàçìåð ÷èñåë â öèôðàõ */
{
    int i;                    /* èäåêñíàÿ ïåðåìåííàÿ öèêëà */
    for(i = 0; i < size; i++) /* îðãàíèçàöèÿ öèêëà ïî i */
        num1[i] = num2[i]; /* ïðèñâîåíèå i-îé öèôðå ÷èñëà num1 i-îé öèôðû ÷èñëà num2 */
}

/*--------------------------------------------------------
    Óìíîæåíèå äëèííîãî ÷èñëà íà öèôðó (*pcf,Res) = num * x
--------------------------------------------------------*/
static void ShortMul(Digit Res[],       /* ðåçóëüòàò (size öèôð) */
                     const Digit num[], /* ïåðâûé ñîìíîæèòåëü (size öèôð) */
                     Digit x,           /* âòîðîé ñîìíîæèòåëü (1 öèôðà) */
                     Digit* pcf,        /* ïåðåíîñ ñòàðøåãî ðàçðÿäà (1 öèôðà), ì.á. NULL */
                     int size)          /* ðàçìåð ÷èñëà â öèôðàõ */
{
    TwoDigit buf; /* ïåðåìåííàÿ äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî ðåçóëüòàòà óìíîæåíèÿ äâóõ ñëîâ */
    Digit cf = 0; /* ïåðåìåííàÿ äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî ðåçóëüòàòà ïåðåíîñà */
    int i; /* èäåêñíàÿ ïåðåìåííàÿ öèêëà */

    for(i = 0; i < size; i++) /* îðãàíèçàöèÿ öèêëà ïî i */
    {
        buf = (TwoDigit)num[i] * x + cf; /* buf - ñóììà ðåóëüòàòà óìíîæåíèÿ è ïðåäûäóùåãî ïåðåíîñà */
        Res[i] = LODIGIT(buf); /* i-ÿ öèôðà Res - ìëàäøàÿ öèôðà buf */
        cf = HIDIGIT(buf);     /* cf - ïåðåíîñ (ñòàðøàÿ öèôðà buf) */
    }
    if(pcf)
        *pcf = cf; /* åñëè àäðåñ pcf íå 0, âîçâðàùàåì ïåðåíîñ */
}

/*--------------------------------------------------------
    Äåëåíèå äëèííîãî ÷èñëà íà öèôðó Res = num/x, *pmod = num % x
--------------------------------------------------------*/
static void ShortDiv(Digit Res[],       /* ÷àñòíîå (size öèôð) */
                     const Digit num[], /* äåëèìîå  (size öèôð) */
                     Digit x,           /* äåëèòåëü (öèôðà) */
                     Digit* pmod,       /* îñòàòîê (öèôðà), ì.á. NULL */
                     int size)          /* ðàçìåð äëèííûõ ÷èñåë â öèôðàõ */
{
    TwoDigit buf = 0; /* âñïîìîãàòåëüíàÿ ïåðåìåííàÿ */
    int i;            /* èäåêñíàÿ ïåðåìåííàÿ öèêëà */

    if(!x)
        return; /* åñëè x ðàâåí 0 òî áåññëàâíî çàâåðøàåì äåëåíèå */
    for(i = size - 1; i >= 0; i--) /* îðãàíèçàöèÿ öèêëà ïî i */
    {
        buf <<= sizeof(Digit) * 8; /* ñòàðøàÿ öèôðà buf - ïðåäûäóùèé îñòàòîê */
        buf |= num[i];             /* ìëàäøàÿ öèôðà buf - i-ÿ öèôðà ÷èñëà num */
        Res[i] = LODIGIT(buf / x); /* i-ÿ öèôðà Res - ðåçóëüòàò äåëåíèÿ */
        buf %= x;                  /* ìëàäøàÿ öèôðà buf - îñòàòîê */
    }
    if(pmod)
        *pmod = LODIGIT(buf); /* åñëè àäðåñ pmod íå 0, âîçâðàùàåì îñòàòîê */
}
/*--------------------------------------------------------
    Äåëåíèå äëèííûõ ÷èñåë Q = U/V, R = U % V
    Èñêëþ÷åíèå äåëåíèÿ íà 0 íå îáðàáàòûâàåòñÿ
--------------------------------------------------------*/
void Div(const Digit U[], /* äåëèìîå (sizeU öèôð) */
         const Digit V[], /* äåëèòåëü (sizeV öèôð) */
         Digit Q[],       /* ÷àñòíîå (sizeU öèôð), ì.á. NULL */
         Digit R[],       /* îñòàòîê (sizeV öèôð), ì.á. NULL */
         int sizeU, int sizeV)
{
    Digit q, buf1, buf2;                /* äëÿ ïðîìåæóòî÷íîãî õðàíåíèÿ */
    Digit U2[MAX_DIV_OPERAND_SIZE + 1], /* äëÿ íîðìàëèçîâàííîãî U */
        V2[MAX_DIV_OPERAND_SIZE + 1];   /* äëÿ íîðìàëèçîâàííîãî V */
    TwoDigit inter;                     /* äëÿ ïðîìåæóòî÷íûõ îïåðàöèé */
    int i, j, k;                        /* èíäåêñíûå ïåðåìåííûå */
    Digit d;                            /* íîðìàëèçóþùèé ìíîæèòåëü */

    for(int i = 0; i < 65; i++) {
        U2[i] = 0;
        V2[i] = 0;
    }
    /*--- Ïðîâåðêè, ïîäãîòîâêà: */
    if(R)
        Zero(R, sizeV); /* åñëè àäðåñ îñòàòêà R íå 0, îáíóëÿåì îñòàòîê */
    if(Q)
        Zero(Q, sizeU); /* åñëè àäðåñ ÷àñòíîãî Q íå 0, îáíóëÿåì ÷àñòíîå */

    for(i = sizeV - 1; (i >= 0) & (!V[i]); i--)
        ;          /* àíàëèç äåëèòåëÿ, îòñåêàåì ñòàðøèå íåçíà÷àùèå íóëè */
    sizeV = i + 1; /* íîâûé ðàçìåð äåëèòåëÿ */
    if(!sizeV)
        return; /* èñêëþ÷åíèå "Äåëåíèå íà íîëü" (ïðîñòî óõîäèì) */

    for(k = sizeU - 1; (k >= 0) & (!U[k]); k--)
        ;          /* àíàëèç äåëèìîãî, îòñåêàåì ñòàðøèå íåçíà÷àùèå íóëè */
    sizeU = k + 1; /* íîâûé ðàçìåð äåëèìîãî */

    if(sizeV > sizeU) /* åñëè äåëèòåëü áîëüøå äåëèìîãî, òî */
    {
        if(R)
            Assign(R, U, sizeU); /* îñòàòîê ðàâåí äåëèìîìó */
        return;                  /* óõîäèì */
    } else if(sizeV == 1)        /* åñëè äåëèòåëü - 1 öèôðà, òî */
    {
        ShortDiv(Q, U, V[0], R, sizeU); /* ïðèìåíÿåì óïðîùåííûé àëãîðèòì */
        return;                         /* óõîäèì */
    }

    /*--- Íîðìàëèçàöèÿ: */
    d = (Digit)(((TwoDigit)MAXDIGIT + 1) / ((TwoDigit)V[sizeV - 1] + 1)); /* íîðìàëèçóþùèé ìíîæèòåëü */
    if(d != 1)                                                            /* åñëè d íå 1, */
    {
        ShortMul(V2, V, d, &buf1, sizeV); /* óìíîæàåì V íà d */
        V2[sizeV] = buf1;
        ShortMul(U2, U, d, &buf1, sizeU); /* óìíîæàåì U íà d */
        U2[sizeU] = buf1;
    } else {                  /* åñëè d == 1, */
        Assign(V2, V, sizeV); /* V2 = V */
        V2[sizeV] = 0;
        Assign(U2, U, sizeU); /* U2 = U */
        U2[sizeU] = 0;
    }
    /*--- Îñíîâíîé öèêë */
    for(j = sizeU; j >= sizeV; j--) /* îðãàíèçàöèÿ ãëàâíîãî öèêëà ïî j (sizeU-sizeV ðàç) */
    {
        /*--- Î÷åðåäíàÿ öèôðà ÷àñòíîãî */
        inter = MAKE_TWO_DIGIT(U2[j], U2[j - 1]); /* ïðèãîäèòñÿ */
        if(U2[j] == V2[sizeV - 1])                /* åñëè ñòàðøèå öèôðû ðàâíû, */
            q = MAXDIGIT;                         /* öèôðà ÷àñòíîãî q = MAXDIGIT */
        else                                      /* èíà÷å */
            q = (Digit)(inter / V2[sizeV - 1]); /* j-þ öèôðó ÷àñòíîãî q íàõîäèì äåëåíèåì */
                                                /* åñëè q âåëèêîâàò, */

        /*--- Âû÷èòàíèå êðàòíîãî äåëèòåëÿ */
        ShortMul(R, V2, q, &buf1, sizeV);                     /* óìíîæàåì V íà q */
        Sub(U2 + j - sizeV, U2 + j - sizeV, R, &buf2, sizeV); /* âû÷èòàåì ðåçóëüòàò óìíîæåíèÿ */
        inter = (LongDigit)U2[j] - buf1 - buf2;
        U2[j] = LODIGIT(inter);

        /*--- Êîððåêöèÿ îñòàòêà è ÷àñòíîãî */
        if(HIDIGIT(inter)) /* åñëè ðåçóëüòàò øàãà îòðèöàòåëüíûé, */
        {                  /* êîìïåíñèðóþùåå ñëîæåíèå */
            Add(U2 + j - sizeV, U2 + j - sizeV, V2, &buf2, sizeV);
            U2[j] += buf2;
            q--; /* êîððåêöèÿ öèôðû ÷àñòíîãî q íà 1 */
        }
        if(Q)                 /* åñëè àäðåñ ÷àñòíîãî Q íå 0, */
            Q[j - sizeV] = q; /* çàïîìèíàåì j-þ öèôðó ÷àñòíîãî q */
    }
    /*--- Çàâåðøåíèå */
    if(R) /* åñëè àäðåñ îñòàòêà R íå 0, */
    {
        ShortDiv(R, U2, d, NULL, sizeV); /* äåíîðìàëèçàöèÿ îñòàòêà R */
    }
}
void Mod_Div(const Digit U[], /* äåëèìîå (sizeU öèôð) */
             const Digit V[], /* äåëèòåëü (sizeV öèôð) */
             Digit Q[])       /* Îñòàòîê */

{
    Digit* cel = new Digit[CD];
    Div(U, V, cel, Q, CD, CD);
    delete[] cel;
}
void Int_Div(const Digit U[], /* äåëèìîå (sizeU öèôð) */
             const Digit V[], /* äåëèòåëü (sizeV öèôð) */
             Digit Q[])       /* Öåëàÿ ÷àñòü */

{
    Digit* mod = new Digit[CD];
    Div(U, V, Q, mod, CD, CD);
    delete[] mod;
}

/*--------------------------------------------------------
    Óìíîæåíèå ÷èñåë
--------------------------------------------------------*/

void Mult(const Digit first[],  /*Ïåðâûé ìíîæèòåëü*/
          const Digit second[], /*Âòîðîé ìíîæèòåëü*/
          Digit Res[]           /*Ïðîèçâåäåíèå*/
)
{
    TwoDigit buf; /* ïåðåìåííàÿ äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî ðåçóëüòàòà óìíîæåíèÿ äâóõ ñëîâ */
    Digit cf = 0; /* ïåðåìåííàÿ äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî ðåçóëüòàòà ïåðåíîñà */
    int i, j; /* èäåêñíàÿ ïåðåìåííàÿ öèêëà */
    Digit* Res2 = new Digit[2 * CD];
    for(i = 0; i < 2 * CD; i++) {
        Res2[i] = 0;
    }
    for(i = 0; i < CD; i++) {
        cf = 0;
        for(j = 0; j < CD; j++) /* îðãàíèçàöèÿ öèêëà ïî i */
        {
            buf = (TwoDigit)first[i] * second[j] + Res2[i + j] +
                  cf; /* buf - ñóììà ðåóëüòàòà óìíîæåíèÿ è ïðåäûäóùåãî ïåðåíîñà */
            Res2[i + j] = LODIGIT(buf); /* i-ÿ öèôðà Res - ìëàäøàÿ öèôðà buf */
            cf = HIDIGIT(buf);          /* cf - ïåðåíîñ (ñòàðøàÿ öèôðà buf) */
        }
        Res2[i + CD] = cf;
    }

    Digit* cel = new Digit[2 * CD];
    Div(Res2, g_p, cel, Res, 2 * CD, CD);
    //	cout << NumToStringDigit(cel) << endl;
    //	cout << NumToStringDigit(Res) << endl;
    delete[] cel;
    delete[] Res2;
}
void Mult_q(const Digit first[],  /*Ïåðâûé ìíîæèòåëü*/
            const Digit second[], /*Âòîðîé ìíîæèòåëü*/
            Digit Res[]           /*Ïðîèçâåäåíèå*/
)
{
    TwoDigit buf; /* ïåðåìåííàÿ äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî ðåçóëüòàòà óìíîæåíèÿ äâóõ ñëîâ */
    Digit cf = 0; /* ïåðåìåííàÿ äëÿ õðàíåíèÿ ïðîìåæóòî÷íîãî ðåçóëüòàòà ïåðåíîñà */
    int i, j; /* èäåêñíàÿ ïåðåìåííàÿ öèêëà */
    Digit* Res2 = new Digit[2 * CD];
    for(i = 0; i < 2 * CD; i++) {
        Res2[i] = 0;
    }
    for(i = 0; i < CD; i++) {
        cf = 0;
        for(j = 0; j < CD; j++) /* îðãàíèçàöèÿ öèêëà ïî i */
        {
            buf = (TwoDigit)first[i] * second[j] + Res2[i + j] +
                  cf; /* buf - ñóììà ðåóëüòàòà óìíîæåíèÿ è ïðåäûäóùåãî ïåðåíîñà */
            Res2[i + j] = LODIGIT(buf); /* i-ÿ öèôðà Res - ìëàäøàÿ öèôðà buf */
            cf = HIDIGIT(buf);          /* cf - ïåðåíîñ (ñòàðøàÿ öèôðà buf) */
        }
        Res2[i + CD] = cf;
    }
    Digit* cel = new Digit[2 * CD];

    Div(Res2, g_q, cel, Res, 2 * CD, CD);
    delete[] cel;
    delete[] Res2;
}