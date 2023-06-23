from setuptools import Extension, setup

file = input('File: ')

setup(
	ext_modules=[Extension(
		name=file.split('.')[0],
		sources=[file],
		language='c++'
	)]			
)