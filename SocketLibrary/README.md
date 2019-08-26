Copyright @Ravi Prasad (India)

---------------------------------------
About
----------------------------------------
This repo servers two things.
	1. Deployment of posix socket library (blocking and non blocking)
	2. Uses of the socket library with the ClietSever Module.

Uses
--------------------------------------
1. git clone <This repo>
2. go to SocketLibrary.
3. Run make.

After Make, it will create client and server exe as follows.
For RHEL, CENTOS 7, BSD

SocketLibrary/ClientServer/client/Linux/client
SocketLibrary/ClientServer/server/Linux/server

----------------------------------------
Running the client and server

From Server Host 1: Run server &
From Client Host 1: Run client <server Host 1 IP or name>
										send some message to the server, server will reply the same message.
From Client Host 2: Run client <server Host 1 IP or name>
										send some message to the server, server will reply the same message.
From Client Host 3: Run client <server Host 1 IP or name>
										send some message to the server, server will reply the same message.
From Client Host 3: Run client <server Host 1 IP or name>
										send some message to the server, server will reply the same message.

Multiple client can communicate with the server.

---------------------End------------------



