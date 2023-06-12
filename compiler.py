from os import popen, getenv
from os.path import exists

class CompilerNotFoundError(Exception): pass

class Compiler:
	
	def __init__(self):
		pythonpath = getenv("%PYTHONPATH%")
		