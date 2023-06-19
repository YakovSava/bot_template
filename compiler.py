from os import listdir
from setuptools import Extension, setup

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

		exec(f"import {file.split('.')[0]}")