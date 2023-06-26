from sys import executable, platform
from os import popen, listdir, system
from Cython.Build import cythonize as _cythonize_back

class NoCompilerError(Exception): pass

COMPILER = None
ARGS = []

def _get_args() -> list[str]:
	if platform == 'win32':
		path = executable.rsplit('\\', 1)[0]
		include = path+'\\include'
		libs = path+'\\libs'
	else:
		include = '/usr/bin/include/python3'
		libs = include
	return ['-shared', f'-I{include}', f'-I{libs}', '-fPIC']

def _get_compiler() -> str:
	check_gcc = popen('gcc')
	check_clang = popen('clang')
	if platform == 'win32':
		if check_gcc.startswith('"gcc"') or check_gcc.startswith('gcc : '):
			if check_clang.startswith('"clang"') or check_gcc.startswith('clang : '):
				raise NoCompilerError('NO gcc or clang!')
			return 'clang++'
		return 'g++'
	else:
		return 'g++'

def _cythonize() -> None:
	_cythonize_back([file for file in listdir() if file.endswith(('.pyx', '.pxd'))]) # Not compile

def _get_compiler_files() -> list[str]:
	return [
		file for file in listdir() if file.endswith(
			'.c', '.h', '.cc',
			'.hpp', '.cpp', '.cxx',
			'.h++', '.hh', '.hxx'
		)
	]

def _compile() -> None:
	if platform == 'win32':
		end = '.pyd'
	else:
		end = '.so'

	global COMPILER, ARGS
	COMPILER = _get_compiler()
	ARGS = _get_args()
	_cythonize()
	files = _get_compiler_files()
	for file in files:
		system(f'{COMPILER} {" ".join(ARGS)} {file} -o {file.split(".")[0]+end}')



def compile() -> None:
	_compile()

if __name__ == '__main__':
	compile()