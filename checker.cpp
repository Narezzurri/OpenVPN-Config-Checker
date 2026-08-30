#include	<windows.h>
#include	<iostream>
#include	<vector>
using namespace std;
using db = double;

string s;
int T = -1;
char cmd[300];
int a, b, c, d;
int ping_cnt = 0;
db sec_per_wait = 1;
db ping_timeout = 1;

/* @brief read a non-negative integer from [s] and store it in [ans] */
inline int get_int (const char *s, int &ans)
{
	for (int i = 0; s[i]; i++) if (!isdigit (s[i]))
		return 1;
	return sscanf (s, "%d", &ans) <= 0 || ans < 0;
}

/* @brief read a non-negative decimal fraction from [s] and store it in [ans] */
inline int get_float (const char *s, db &ans)
{
	for (int i = 0; s[i]; i++) if (!isdigit (s[i]) && s[i] != '.')
		return 1;
	return sscanf (s, "%lf", &ans) <= 0 || ans < 0;
}

signed main (signed argc, const char* argv[])
{
	vector<int> mark (argc);
	for (int i = 1; i < argc; i++) if (argv[i][0] == '/') [&] ()
	{
		mark[i] = 1;
		int nxt = i;
		if (i == argc - 1 || [&] () -> bool
		{
			string arg = argv[i];
			if (arg == "/t")
				return get_int (argv[++nxt], T) || get_float (argv[++nxt], sec_per_wait);
			else if (arg == "/w")
				return get_float (argv[++nxt], ping_timeout);
			else if (arg == "/n")
				return get_int (argv[++nxt], ping_cnt);
			else
				fprintf (stderr, "Unrecognized argument : %s.Skip\n", argv[i]);
			return 0;
		}())
			fprintf (stderr, "Miss or Invalid argument for argument %d : %s.Skip\n", i, argv[i]);
		else
		{
			for (int j = nxt; j > i; j--)
				mark[j] = 1;
		}
	} ();
	int cnt = 0;
	for (int i = 1; i < argc; i++) if (!mark[i])
	{
		if (T > 0 && cnt && !(cnt % T))
			Sleep (sec_per_wait * 1000);
		fprintf (stderr, "%s: ", argv[i]);
		s = argv[i];
		if (s.substr(s.find_last_of('.')) != ".ovpn")
			fprintf (stderr, "Unsupported file type.\n");
		else
		{
			cin.clear();
			freopen (argv[i], "r", stdin);
			cin >> s;
			while (cin >> s && s != "remote");
			if (s != "remote")
				fprintf (stderr, "Server ip address not found.\n");
			else
			{
				cin >> s;
				string name = argv[i];
				name = name.substr(name.find_last_of('\\') + 1).data();
				sprintf (cmd, "start %s \"%s\" cmd /c \"ping %s -w %d ", ~T ? "" : "/wait", name.data(), s.data(), (int) (ping_timeout * 1e3), ping_cnt);
				if (ping_cnt)
					sprintf (cmd + strlen (cmd), "-n %d\"\n", ping_cnt);
				else
					sprintf (cmd + strlen (cmd), "-t\"\n");
				system (cmd);
				cnt++;
				fprintf (stderr, "Done.\n");
			}
		}
	}
	cout << cnt << " files checked successfully" << endl;
	freopen ("CON", "r", stdin);
	getchar ();
	return 0;
}
