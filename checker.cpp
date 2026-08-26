#include	<windows.h>
#include	<iostream>
#include	<vector>
using namespace std;
using db = double;

string s;
int T = -1;
char cmd[300];
int a, b, c, d;
int ping_cnt = 4;
db sec_per_wait = 0;
db ping_timeout = 1;

inline int isint (const char *s)
{
	for (int i = 0; s[i]; i++) if (!isdigit (s[i]))
		return 0;
	return 1;
}

inline int isfloat (const char *s)
{
	for (int i = 0; s[i]; i++) if (isdigit (s[i]) && s[i] != '.')
		return 0;
	return 1;
}

signed main (signed argc, const char* argv[])
{
	vector<int> mark (argc);
	mark[0] = 1;
	for (int i = 1; i < argc; i++) if (argv[i][0] == '/') [&] ()
	{
		mark[i] = 1;
		if (i == argc - 1 || [&] () -> bool
		{
			switch (argv[i][1])
			{
				case 't':
					if (!isfloat (argv[++i]) || sscanf (argv[i], "%lf", &sec_per_wait) <= 0)
						return 1;
					else if (sec_per_wait < 0)
						printf ("Invalid parameter for argument %d : %s.Time(%s here) cannot be negative.", i - 1, argv[i - 1], argv[i]);
					break;
				case 'v':
					if (!isint (argv[++i]) || sscanf (argv[i], "%d", &T) <= 0)
						return 1;
					break;
				case 'w':
					if (!isfloat (argv[++i]) || sscanf (argv[i], "%lf", &ping_timeout) <= 0)
						return 1;
					break;
				case 'n':
					if (!isint (argv[++i]) || sscanf (argv[i], "%d", &ping_cnt) <= 0)
						return 1;
					break;
				default:
					printf ("Unrecognized parameter : %s.Skip\n", argv[i]);
			}
			return 0;
		}())
		{
			printf ("Miss parameter for argument %d : %s.Skip\n", i - 1, argv[i - 1]);
			if (i == argc - 1)
				return ;
			i--;
		}
		mark[i] = 1;
	} ();
	int cnt = 0;
	for (int i = 1; i < argc; i++) if (!mark[i])
	{
		if (T > 0 && cnt && !(cnt % T))
			Sleep (sec_per_wait * 1000);
		printf ("%s: ", argv[i]);
		s = argv[i];
		if (s.length() < 5 || s.substr(s.length() - 5) != ".ovpn")
			puts ("Unsupported file type.");
		else
		{
			cin.clear();
			freopen (argv[i], "r", stdin);
			cin >> s;
			while (cin >> s && s != "remote");
			if (s != "remote")
				puts ("Server ip address not found.");
			else
			{
				cin >> s;
				string name = argv[i];
				name = name.substr(name.find_last_of('\\') + 1).data();
				if (T < 0)
					sprintf (cmd, "title %s && ping %s -w %d -n %d", name.data(), s.data(), (int) (ping_timeout * 1e3), ping_cnt);
				else
					sprintf (cmd, "start \"%s\" cmd /c \"ping -t %s -w %d -n %d\"\n", name.data(), s.data(), (int) (ping_timeout * 1e3), ping_cnt);
				system (cmd);
				cnt++;
				puts ("Done.");
			}
		}
	}
	cout << cnt << " files checked successfully" << endl;
	freopen ("CON", "r", stdin);
	getchar ();
	return 0;
}
