from compiler import Compiler

def IMPORT_MODULE(from_, module):
	exec(f"global {module}; from {from_} import {module}")

compiler = Compiler()

for module in ["binder.cpp", "damerau_levenshtein.cxx"]:
	module_name = compiler.compile(module)
	IMPORT_MODULE(module_name, module_name)

del compiler

from jsexec import TemporaryFile, JSExec