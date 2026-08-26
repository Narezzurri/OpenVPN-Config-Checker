#include	<iostream>
using namespace std;

string s;
char cmd[300];
int a, b, c, d;

signed main (signed argc, const char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		freopen (argv[i], "r", stdin);
		cin >> s;
		while (s != "remote")
			cin >> s;
		scanf ("%d.%d.%d.%d", &a ,&b, &c, &d);
		s = argv[i];
		if (s.length() < 5 || s.substr(s.length() - 5) != ".ovpn")
			printf ("%s is of an unsupported file type.", argv[i]);
		else
		{
			sprintf (cmd, "start \"%s\" cmd /c \"ping -t %d.%d.%d.%d\"\n", s.substr(s.find_last_of('\\') + 1).data(), a, b, c, d);
			system (cmd);
		}
		fclose (stdin);
	}
	puts ("Done.");
	return 0;
}
