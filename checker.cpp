#include	<iostream>
using namespace std;

string s;
char cmd[300];
int a, b, c, d;

signed main (signed argc, const char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		printf ("%s: ", argv[i]);
		freopen (argv[i], "r", stdin);
		while (cin >> s && s != "remote");
		if (s != "remote")
			puts ("Server ip address not found.");
		else
		{
			scanf ("%d.%d.%d.%d", &a ,&b, &c, &d);
			s = argv[i];
			if (s.length() < 5 || s.substr(s.length() - 5) != ".ovpn")
				puts ("Unsupported file type.");
			else
			{
				sprintf (cmd, "start \"%s\" cmd /c \"ping -t %d.%d.%d.%d\"\n", s.substr(s.find_last_of('\\') + 1).data(), a, b, c, d);
				system (cmd);
				puts ("Done.");
			}
		}
		fclose (stdin);
	}
	return 0;
}
