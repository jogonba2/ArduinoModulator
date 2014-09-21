#!/usr/bin/env python
# -*- coding: utf-8 -*-
import socket,serial

class ParseResponse:
	
	# Serial devolverá 1 byte
	# Los 4 bits de mayor peso indicarán el módulo del que proviene la resp
	# Los 4 bits de menor peso indican el código de respuesta
	# Códigos de respuesta:
	# 0 -> Acción realizada
	# 1 -> Arduino no alimentado
	# 2 -> Problema de red
	# 3 -> Módulo no inicializado (no alimentado)
	# 4 -> Error App (IO)
	# ...
	# n -> n
	
	# Remote Interact
	@staticmethod
	def __interact__(error,sck):
		sck.send("\n"+error+"\n")
		#while resp != 0b0000:
		#
		#
		######################	
			
		
	# It manages errors and call error function&solve
	@staticmethod
	def __parseError__(resp,sck):
		errorList = {"0000":"Accion realizada correctamente",
					 "0001":"Error conexión arduino",
					 "0010":"Problema de red",
					 "0001":"Módulo no alimentado",
					 "1111":"Error en la aplicación"
					 }
		ParseResponse.__interact__(errorList[resp],sck)	
				
class ServerSocket:
	
	def __init__(self):
		self.sck = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
		self.sck.bind(("localhost",1337))
		self.sck.listen(1)
		self.serialDescriptor = serial.Serial('COM4',9600)
		self.sckClient, addr = self.sck.accept()
				
	def _listen(self):
		# Si se quiere implementar instrucciones seguidas hacerlo del lado del cliente #
		command = self.sckClient.recv(1024)		
		# Enviar serial
		self.__useSerial(command)
		# Recibir serial
		response = self.__useSerial()
		# Parsear la respuesta del terminal.
		ParseResponse.__parseError__((bin(ord(response[0])))[-4:],self.sckClient)	
	
	def __useSerial(self,*args):
		def _sendSerial(wSer,args):
			wSer.write(args[0][0])
			try:
				wSer.write(args[0][1])
				wSer.flush()
			except:
				pass
		
		def _recvSerial(wSer):
			auxW = wSer.readline()
			return auxW
		
		wSer = self.serialDescriptor
		if len(args)>0:
			_sendSerial(wSer,args)
			return
		else:
			return _recvSerial(wSer)
		return ParseResponse.__parseError__("1111",self.sckClient)
					
		
	def _close(self):
		self.serialDescriptor.close()
		self.sck.close()

if __name__ == '__main__':
	sSocket = ServerSocket()
	while True:
		try:
			sSocket._listen()
		except:
			# Restart Socket
			continue
	sSocket._close()
