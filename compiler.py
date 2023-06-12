from sys import platform
from os import popen, getenv, system
from os.path import exists

class CompilerNotFoundError(Exception): pass

class Compiler:
	
	def __init__(self):
		self.pythonpath = getenv("%PYTHONPATH%")
		if self._check_gcc():
			self.compiler = "g++"
		elif self._check_clang():
			self.compiler = "clang++"
		else:
			raise CompilerNotFoundError("Install GCC or Clang compiler please!")
		if platform == "win32":
			self.splitter = "\\"
		else:
			self.splitter = "/"
	
	def _check_gcc(self):
		if popen("g++ --version").read().lower().startswith("g++"):
			return True
		return False
	
	def _check_clang(self):
		if popen("clang++ --version").read().lower().startswith("clang"):
			return True
		return False
	
	def compile(self, filename:str):
		name = filename.split(".")[0]
		system(f"{self.compiler} -o {name}.pyd {filename} -shared -I{self.pythonpath}{self.splitter}include -L{self.pythonpath}{self.splitter}lib")
		return name