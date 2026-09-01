#include	<sstream>
#include	"lib.h"
using namespace std;

int get_int (const char *s, int &ans)
{
	for (int i = 0; s[i]; i++) if (!isdigit (s[i]))
		return 1;
	return stringstream (s) >> ans && ans >= 0;
}

int get_float (const char *s, db &ans)
{
	for (int i = 0; s[i]; i++) if (!isdigit (s[i]) && s[i] != '.')
		return 1;
	return stringstream (s) >> ans && ans >= 0;
}

string quote (string s)
{
	return '"' + s + '"';
}

string extract (string s, char c)
{
	if (int idx = s.find_last_of (c); idx == string::npos)
		return "";
	else
		return s.substr (idx);
}
