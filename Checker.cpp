#include	<windows.h>
#include	<iostream>
#include	<sstream>
#include	<vector>
#include	"lib.h"
using namespace std;
using db = double;

int T = -1;
int a, b, c, d;
int ping_cnt = 0;
db sec_per_wait = 1;
db ping_timeout = 1;

int main (int argc, const char* argv[])
{
	if (HelpDetected (argc, argv))
	{
		cout << endl << string {
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
		vector<string> files = Search (argv[i]);
		for (auto filename : files)
		{
			cerr << filename << " : ";
			if (extract (filename, '.') != ".ovpn")
				fputs ("Unsupported file type.\n", stderr);
			else
			{
				cin.clear();
				freopen (filename.c_str(), "r", stdin);
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
					if (string s = extract (filename, '\\'); !s.empty())
						filename = s;
					string cmd = "start " + quote (filename) + " cmd /c " + quote (ping);
					if (!~T)
						cmd = "start /wait" + cmd.substr(5);
					system (cmd.c_str());
					cnt++;
					fputs ("Done.\n", stderr);
				}
			}
		}
	}
	cerr << cnt << " files checked successfully." << endl;
	freopen ("CON", "r", stdin);
	getchar ();
	return 0;
}
