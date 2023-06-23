from sys import platform
from os import listdir, system
from jsexec import JSeval, JSexec

if platform == 'win32':
	system('python compiler.py build_ext --inplace')
else:
	system('python3 compiler.py build_ext --inplace')

for file in listdir():
	if file.endswith((
		'.c', '.h', '.cc',
		'.hpp', '.cpp', '.cxx',
		'.h++', '.hh', '.hxx'
	)):
		exec(f"import {file.split('.')[0]}")

from recomendate import recomendate