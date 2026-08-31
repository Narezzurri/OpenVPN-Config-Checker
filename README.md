No collaborators yet.

Welcome to join and contribute issues.

# Checker 

A command-line-based Win32 software to check in bulk the connection between the host and the remote VPN server which is recorded in the OpenVPN config files (\*.ovpn).

## Usage 

`> checker <param1> <param2> config1.ovpn config2.ovpn ...` 

### Arguments 

If there exist multiple arguments with the same type,only the last one affect.

- `/t period [time]` 

	Customize the efficiency,that is,the number of valid files to process at once.
	
	Set `0` to process all files at once,and set `-1` to process each file one by one,which is default.

	Otherwise,you can assign an extra parameter `time`.
	
	It decides the time to break after process a certain bulk of files.

	`time` can be a float number,default is `1`.

	If `time` is reserved,it'll reset whether it was assigned before.

	**Warning**: Process too many files at once may cause the system crashing.

- `/w timeout` 

	Customize the timeout[s] for every ping,default is `1`.

	`timeout` can be a float number.

- `/n count` 

	Customize the number of ping(s) per file,default is $\infty$,that is,stop until you close the window.

In addition, you can drag the target config file onto `checker.exe` to start the programme by default settings.

***

# Authenticator

A command-line-based Win32 software to append login credential file to OpenVPN config files (\*.ovpn).

## Usage

`> Auth config1.ovpn config2.ovpn ...` 

### Arguments

The default login credential file is `auth.txt` 
