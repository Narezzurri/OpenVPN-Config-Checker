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
	for (int i = 0; s[i]; i++) if (!isdigit (s[i]) && s[i] != '.')
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
				case 'v':
					if (!isint (argv[++i]) || sscanf (argv[i], "%d", &T) <= 0)
						return 1;
					break;
				case 't':
					if (!isfloat (argv[++i]) || sscanf (argv[i], "%lf", &sec_per_wait) <= 0)
						return 1;
					else if (sec_per_wait < 0)
						fprintf (stderr, "Invalid parameter for argument %d : %s.Time(%s here) cannot be negative.", i - 1, argv[i - 1], argv[i]);
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
					fprintf (stderr, "Unrecognized parameter : %s.Skip\n", argv[i]);
			}
			return 0;
		}())
		{
			fprintf (stderr, "Miss parameter for argument %d : %s.Skip\n", i - 1, argv[i - 1]);
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
				if (T < 0)
				{
					if (ping_cnt)
						sprintf (cmd, "start /wait \"%s\" cmd /c \"ping %s -w %d -n %d\"\n", name.data(), s.data(), (int) (ping_timeout * 1e3), ping_cnt);
					else
						sprintf (cmd, "start /wait \"%s\" cmd /c \"ping %s -w %d -t\"\n", name.data(), s.data(), (int) (ping_timeout * 1e3));
				}
				else
				{
					if (ping_cnt)
						sprintf (cmd, "start \"%s\" cmd /c \"ping %s -w %d -n %d\"\n", name.data(), s.data(), (int) (ping_timeout * 1e3), ping_cnt);
					else
						sprintf (cmd, "start \"%s\" cmd /c \"ping %s -w %d -t\"\n", name.data(), s.data(), (int) (ping_timeout * 1e3));
				}
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
