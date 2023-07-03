from time import time
from random import randint as py_randint
from rand import randint as c_randint

def timeit(func:callable):
	def wrapper(*args, **kwargs):
		start = time()
		func(*args, **kwargs)
		end = time()
		return end - start
	return wrapper

@timeit
def py_rander():
	for _ in range(1000000):
		py_randint(0, 1000)

@timeit
def c_rander():
	for _ in range(1000000):
		c_randint(0, 1000)

if __name__ == '__main__':
	print('Rander Python: ', py_rander())
	print('Rander C++: ', c_rander())