from sys import platform
from os import listdir, system
from jsexec import JSeval, JSexec
from gcc_clang_compiler import compile

if platform == 'win32':
	system('python compiler.py build_ext --inplace')
else:
	system('python3 compiler.py build_ext --inplace')

compile()

for file in listdir():
	if file.endswith('.pyd'):
		exec(f"import {file.split('.')[0]}")

from recomendate import recomendate
from Crandom import choice, randint, nrandint,\
	randrange, shuffle, nchoice