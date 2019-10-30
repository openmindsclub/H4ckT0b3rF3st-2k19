#!/usr/bin/python3

"""
	Author : BITAM SALIM
	GITHUB : https://github.com/soolidsnake/

"""


import socket
from threading import Thread
import time



clients_info=[]
stop = False
#Accepts a client connection
def accept_connection(main_connection):
	global clients_info
	while True:
		client, address = main_connection.accept()
		client.settimeout(5)
		try:
			clients_info.append(client)
		except socket.error:
			continue



def main():

	# Listen for the client connection.
	main_connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	main_connection.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # To refuse the socket if it is in time_wait
	main_connection.bind(("0.0.0.0", 12345))
	main_connection.listen(50)

	# drop dat thread to listen for upcoming clients
	th_listen = Thread(target=accept_connection, args=(main_connection,), daemon=True)
	th_listen.start()

	print('Waiting for clients to connect')
	time.sleep(10)
	print('Shutdown all')

	while True:

		for client in clients_info:
			try:
				client.send('shutdown'.encode())
				client.close()
			except socket.error:
				continue


	main_connection.close()



if __name__ == "__main__":
	main()
