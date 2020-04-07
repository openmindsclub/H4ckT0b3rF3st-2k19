#!/usr/bin/python3

"""
	Author : BITAM SALIM
	GITHUB : https://github.com/soolidsnake/

"""


import socket
from threading import Thread
import datetime
import time
import os

command = 'systemctl poweroff' #command to shutdown
def time_shutdown():
    while 1:
        if datetime.datetime.now().hour > 20:#time to shutdown the PCs
            os.system(command)
        time.sleep(10)



def main():
	th_shut = Thread(target=time_shutdown, args=(), daemon=True)
	th_shut.start()

	
	HOST, PORT = '0.0.0.0', 12345
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	
	while True:
		try:
			sock.connect((HOST, PORT))#connect to the server
			break

		except socket.error:
			time.sleep(5)#sleep then try again
			continue

	while True:
		msg = sock.recv(32)
		if msg.decode() == 'shutdown':
			os.system(command)
			sock.close()
			exit(0)



if __name__ == "__main__":
    main()
