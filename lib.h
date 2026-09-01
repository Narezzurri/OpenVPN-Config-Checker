#include	<string>
using namespace std;
using db = double;

/* @brief read a non-negative integer from [s] and store it in [ans] */
int get_int (const char *s, int &ans);
/* @brief read a non-negative decimal fraction from [s] and store it in [ans] */
int get_float (const char *s, db &ans);
/* @brief wrap a string with quotes */
string quote (string s);
/* @brief extract a substring from [s] up to the last occurrence of [c] (included) */
string extract (string s, char c);
