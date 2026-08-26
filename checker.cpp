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
				string t = argv[i];
				sprintf (cmd, "start \"%s\" cmd /c \"ping -t %s\"\n", t.substr(t.find_last_of('\\') + 1).data(), s.data());
				system (cmd);
				puts ("Done.");
			}
			// fclose (stdin);
		}
	}
	return 0;
}
