from os import listdir
from setuptools import Extension, setup
from Cython.Build import cythonize

for file in listdir():
	if file.endswith((
		'.c', '.h', '.cc',
		'.hpp', '.cpp', '.cxx',
		'.h++', '.hh', '.hxx'
	)):
		setup(
			ext_modules=[Extension(
				name=file.split('.')[0],
				sources=[file],
				language='c++'
			)]			
		)

	elif file.endswith(('.m', '.mm')):
		setup(
			ext_modules=[Extension(
				name=file.split('.')[0],
				sources=[file],
				language='objc++'
			)]
		)

	elif file.endswith('.pyx'):
		setup(
			ext_modules=cythonize([file])
		)

	try: exec(f"import {file.split('.')[0]}")
	except: print(f"{file.split('.')[0]} not imported!")