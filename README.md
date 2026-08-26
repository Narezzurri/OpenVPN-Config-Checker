# OpenVPN-Config-Checker 

A practical Win32 software to check in batch the connection between the host and remote VPN server,which is recorded in the OpenVPN config file (\*.ovpn).

## Function 

- Check if the ip address is available to be connected.(hostname is temporarily unsupported) 

## Usage 

`> checker <param1> <param2> config1.ovpn config2.ovpn ...` 

### Parameters 

- `/v speed` 

	Customize the efficiency,that is,the number of valid files to process at once.
	
	Set `0` to process all files at once,default is `1`.

	**Warning**: Process too many files at once may cause the system to crash.

- `/t time` 

	Customize the time to break after process a bulk of files which is set above.
	
	Set any negative numbers to process the files one by one without starting a new window,which is default.

	`time` can be a float number.

In addition, you can drag the target config file onto `checker.exe` to start the programme by default settings.

## Upcoming Features 

- Generate a list of available server ip address.

- Customize the threshold of ping timeout.

- Customize the number of ping(s) per file.
