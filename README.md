# OpenVPN-Config-Checker 

A practical Win32 software to check in batch the connection between the host and remote VPN server,which is recorded in the OpenVPN config file (\*.ovpn).

## Function 

- Check if the ip address is available to be connected.

## Usage 

`> checker <param1> <param2> config1.ovpn config2.ovpn ...` 

### Parameters 

If there exist multiple arguments with the same type,only the last one affect.

- `/v speed` 

	Customize the efficiency,that is,the number of valid files to process at once.
	
	Set `0` to process all files at once,default is `1`.

	**Warning**: Process too many files at once may cause the system crashing.

- `/t time` 

	Customize the time[s] to break after process a bulk of files which is set above.
	
	Set any negative numbers to process the files one by one,which is default.

	`time` can be a float number.

- `/w timeout` 

	Customize the timeout[s] for every ping,default is `1`.

	`timeout` can be a float number.

- `/n count` 

	Customize the number of ping(s) per file,default is $ \infin $,that is,stop until you close the window.

In addition, you can drag the target config file onto `checker.exe` to start the programme by default settings.

## Upcoming Features 

- Generate a list of available server ip address.

- Add `/wait` switch to replace `/t neg`.
