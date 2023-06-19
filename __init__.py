from os import listdir, system
from jsexec import JSeval, JSexec

system('python compiler.py build_ext --inplace')

for file in listdir():
	if file.endswith((
		'.c', '.h', '.cc',
		'.hpp', '.cpp', '.cxx',
		'.h++', '.hh', '.hxx'
	)):
		exec(f"import {file.split('.')[0]}")