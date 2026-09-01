#include	<windows.h>
#include	<iostream>
#include	<sstream>
#include	<vector>
using namespace std;
using db = double;

int T = -1;
int a, b, c, d;
int ping_cnt = 0;
db sec_per_wait = 1;
db ping_timeout = 1;

/* @brief read a non-negative integer from [s] and store it in [ans] */
inline int get_int (const char *s, int &ans)
{
	for (int i = 0; s[i]; i++) if (!isdigit (s[i]))
		return 1;
	return stringstream (s) >> ans && ans >= 0;
}

/* @brief read a non-negative decimal fraction from [s] and store it in [ans] */
inline int get_float (const char *s, db &ans)
{
	for (int i = 0; s[i]; i++) if (!isdigit (s[i]) && s[i] != '.')
		return 1;
	return stringstream (s) >> ans && ans >= 0;
}

inline string quote (string s)
{
	return '"' + s + '"';
}

string extract (string s, char c)
{
	if (s.find_last_of (c) == string::npos)
		return "";
	else
		return s.substr (0, s.find_last_of (c));
}

int main (int argc, const char* argv[])
{
	if (argc == 1 || [&] ()
	{
		for (int i = 1; i < argc; i++)
		{
			string arg = argv[i];
			if (arg == "--help" || arg == "/?" || arg == "/help")
				return 1;
		}
		return 0;
	}())
	{
		cout << string {
			#embed	"CheckerHelp.txt"
		} << endl;
		return 0;
	}
	vector<int> mark (argc);
	for (int i = 1; i < argc; i++) if (argv[i][0] == '/') [&] ()
	{
		mark[i] = 1;
		int nxt = i;
		if (i == argc - 1 || [&] () -> bool
		{
			string arg = argv[i] + 1;
			if (arg == "t" || arg == "time")
				return get_int (argv[++nxt], T) && get_float (argv[++nxt], sec_per_wait);
			else if (arg == "w" || arg == "wait")
				return get_float (argv[++nxt], ping_timeout);
			else if (arg == "n" || arg == "number")
				return get_int (argv[++nxt], ping_cnt);
			else
			{
				cerr << "Unrecognized argument : " << argv[i] << ".Skip" << endl;
				return 0;
			}
		}())
		{
			for (int j = nxt; j > i; j--)
				mark[j] = 1;
		}
		else
			cerr << "Miss or Invalid argument for argument " << i << " : " << argv[i] << ".Skip" << endl;
	} ();
	int cnt = 0;
	for (int i = 1; i < argc; i++) if (!mark[i])
	{
		if (T > 0 && cnt && !(cnt % T))
			Sleep (sec_per_wait * 1000);
		cerr << argv[i] << " : ";
		string filename = argv[i];
		if (extract (filename, '.') != ".ovpn")
			fputs ("Unsupported file type.\n", stderr);
		else
		{
			cin.clear();
			freopen (argv[i], "r", stdin);
			string addr;
			cin >> addr;
			while (cin >> addr && addr != "remote");
			if (addr != "remote")
				fputs ("Server ip address not found.\n", stderr);
			else
			{
				cin >> addr;				// Server address
				string ping = "ping " + addr + " -w " + to_string ((int) (ping_timeout * 1e3));	// Complete ping command
				if (ping_cnt)
					ping += " -n " + to_string (ping_cnt);
				else
					ping += " -t";
				string cmd = "start " + quote (extract (filename, '\\')) + " cmd /c " + quote (ping);
				if (!~T)
					cmd = "start /wait" + cmd.substr(5);
				system (cmd.data());
				cnt++;
				fputs ("Done.\n", stderr);
			}
		}
	}
	cerr << cnt << " files checked successfully." << endl;
	freopen ("CON", "r", stdin);
	getchar ();
	return 0;
}
