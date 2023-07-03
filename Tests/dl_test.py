from time import time
from dl import damerau_levenshtein_distance

def timeit(func:callable):
	def wrapper(*args, **kwargs):
		start = time()
		func(*args, **kwargs)
		end = time()
		return end - start
	return wrapper

def damerau_levenshtein_distance_python(s1, s2):
	d = {}
	lenstr1 = len(s1)
	lenstr2 = len(s2)
	for i in range(-1,lenstr1+1):
		d[(i,-1)] = i+1
	for j in range(-1,lenstr2+1):
		d[(-1,j)] = j+1

	for i in range(lenstr1):
		for j in range(lenstr2):
			if s1[i] == s2[j]:
				cost = 0
			else:
				cost = 1
			d[(i,j)] = min(
						   d[(i-1,j)] + 1, # deletion
						   d[(i,j-1)] + 1, # insertion
						   d[(i-1,j-1)] + cost, # substitution
						  )
			if i and j and s1[i]==s2[j-1] and s1[i-1] == s2[j]:
				d[(i,j)] = min (d[(i,j)], d[i-2,j-2] + cost) # transposition

	return d[lenstr1-1,lenstr2-1]

def damerau_levenshtein_distance_cpp(s1, s2):
	return damerau_levenshtein_distance(s1, s2)

@timeit
def test_damerau_levenshtein_distance_python():
	for _ in range(100000):
		damerau_levenshtein_distance_python('Тестовый текст', 'Тестовый текст 2 явно является более большим')

@timeit
def test_damerau_levenshtein_distance_cpp():
	for _ in range(100000):
		damerau_levenshtein_distance_cpp('Тестовый текст', 'Тестовый текст 2 явно является более большим')

if __name__ == '__main__':
	print('Damerau levenshtein distance Python: ', test_damerau_levenshtein_distance_python())
	print('Damerau levenshtein distance C++: ', test_damerau_levenshtein_distance_cpp())
	# print(damerau_levenshtein_distance_python('Привет!', 'Првет'))
	# print(damerau_levenshtein_distance_cpp('Привет!', 'Првет'))