project:main.o client.o server.o ipcfifo.o ipcm.o ipcpipe.o speedtest.o ipcshm.o
	gcc main.o  client.o server.o ipcfifo.o ipcm.o ipcshm.o ipcpipe.o speedtest.o -o project
main.o:main.c
	gcc -c main.c -o  main.o
client.o:client.c
	gcc -c client.c -o  client.o
server.o:server.c
	gcc -c server.c -o  server.o
ipcfifo.o:ipcfifo.c
	gcc -c ipcfifo.c -o ipcfifo.o
ipcm.o:ipcm.c
	gcc -c ipcm.c -o ipcm.o
ipcshm.o:ipcshm.c
	gcc -c ipcshm.c -o ipcshm.o
ipcpipe.o:ipcpipe.c
	gcc -c ipcpipe.c -o ipcpipe.o
speedtest.o:speedtest.c
	gcc -c speedtest.c -o speedtest.o
