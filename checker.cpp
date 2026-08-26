#include	<windows.h>
#include	<iostream>
#include	<vector>
using namespace std;
using db = double;

string s;
int T = -1;
char cmd[300];
int a, b, c, d;
db sec_per_wait;

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
					if (sscanf (argv[++i], "%lf", &sec_per_wait) <= 0)
						return 1;
					break;
				case 'v':
					if (sscanf (argv[++i], "%d", &T) <= 0)
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
					sprintf (cmd, "title %s && ping %s -w 1000", name.data(), s.data());
				else
					sprintf (cmd, "start \"%s\" cmd /c \"ping -t %s -w 1000\"\n", name.data(), s.data());
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
