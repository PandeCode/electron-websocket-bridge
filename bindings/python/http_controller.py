#!/bin/env python

import websocket
from typing import Union, Literal, Any
from __future__ import annotations

Type = Union[Literal["info"], Literal["command"], Literal["code"], Literal["error"]]


class Controller:
	def __init__(self, url: str = "ws://localhost:8080/client/ws"):
		self.url = url
		self.ws = websocket.WebSocket()

	def connect(self):
		# pyright-ignore
		self.ws.connect(self.url)
		self.ws.send('{"type": "info", "message": "connected"}')

	def wsTrySend(self, type: Type, message: str) -> None:
		# TODO: Check if connected
		self.ws.send(f'{"type": "{type}", "message": "{message}"}')

	# fmt: off
	def   code(self, code:str)->Any:  self.wsTrySend("code"   ,     code);                 return   self.ws.recv()
	def   getInfo(self):             self.wsTrySend("command" ,    "getInfo");             return   self.ws.recv()
	def   getIsPlaying(self):        self.wsTrySend("command" ,    "getIsPlaying");        return   self.ws.recv()
	def   getRepeatStatus(self):     self.wsTrySend("command" ,    "getRepeatStatus");     return   self.ws.recv()
	def   getIsCurrentLiked(self):   self.wsTrySend("command" ,    "getIsCurrentLiked");   return   self.ws.recv()
	def   dislikeCurrent(self):      self.wsTrySend("command" ,    "dislikeCurrent")
	def   enableRepeat(self):        self.wsTrySend("command" ,    "enableRepeat")
	def   enableRepeatOne(self):     self.wsTrySend("command" ,    "enableRepeatOne")
	def   likeCurrent(self):         self.wsTrySend("command" ,    "likeCurrent")
	def   next(self):                self.wsTrySend("command" ,    "next")
	def   pause(self):               self.wsTrySend("command" ,    "pause")
	def   play(self):                self.wsTrySend("command" ,    "play")
	def   playPause(self):           self.wsTrySend("command" ,    "playPause")
	def   previous(self):            self.wsTrySend("command" ,    "previous")
	def   toggleLike(self):          self.wsTrySend("command" ,    "toggleLike")
	def   toggleShuffle(self):       self.wsTrySend("command" ,    "toggleShuffle")
	# fmt: on

def __main():
	pass

if __name__ == "__main__":
	__main()



