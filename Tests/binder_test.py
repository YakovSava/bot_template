from time import time
from binder import read, write

def timeit(func:callable):
	def wrapper(*args, **kwargs):
		start = time()
		func(*args, **kwargs)
		end = time()
		return end - start
	return wrapper

def _read_python():
	with open('file.txt', 'r') as file:
		return file.read()

def _write_python():
	with open('file.txt', 'w') as file:
		file.write('Test write to file')

@timeit
def _read_write_python():
	for _ in range(100000):
		_read_python()
		_write_python()

@timeit
def _read_write_cpp():
	for _ in range(100000):
		read('file.txt')
		write('file.txt', 'Test write to file')

if __name__ == '__main__':
	print('Read and write 100000 cycles Python: ', _read_write_python())
	print('Read and write 100000 cycles C++: ', _read_write_cpp())