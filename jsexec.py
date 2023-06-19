from os import system
from typing import Any
from json import loads

class TemporaryFile:
	
	def __init__(self, filename:str=".temp"):
		self.file = open(filename, "w+", encoding="utf-8")
		self.filename = filename
	
	def __enter__(self): return self
	
	def __exit__(self): self.file.close()
	
	def write(self, data:Any) -> None:
		self.file.write(str(data))
	
	def read(self) -> str:
		return self.file.read()
	
	def __del__(self):
		self.file.close()


class JSExec:
	
	class NodeNotFoundError(Exception): pass
	
	def __init__(self):
		if not self._check_node():
			raise self.NodeNotFoundError()
	
	def _check_node(self) -> bool:
		with TemporaryFile(filename=".tempCheckNode") as tmp:
			system(f"node --version >> {tmp.filename}")
			return tmp.read().lower().startswith("version")
	
	def jsexec(self,
		filename:str="Example/example.js",
		tmp_filename:str=".node"
	) -> str:
		with TemporaryFile(filename=tmp_filename) as tmp:
			system(f"node {filename} >> {tmp_filename}")
			return loads(tmp.read())