from rand import randint, choice, _overclocking

_overclocking()

def shuffle(lst:list) -> list:
	'''
	Shuffle the list!
	'''
	new_list = []
	for item in lst:
		rindex = randint(0, len(lst))
		new_list.append(lst.pop(rindex))
	return new_list

def randrange(range_min:int, range_max:int) -> range:
	"""
	Get random range
	"""
	while True:
		try: return range(
				randint(range_min, range_max // 2),
				randint(range_min, range_max)
			)
		except: continue

def nrandint(range_min:int, range_max:int, n:int) -> list[int]:
	"""
	Return random list with "n"
	"""
	return [randint(range_min, range_max) for _ in range(n)]

def nchoice(lst:list, n:int) -> list:
	"""
	Return random list with "n" with items from lst
	"""
	return [choice(lst) for _ in range(n)]

if __name__ == '__main__':
	for _ in range(5):
		print(randint(0, 100))
	print("-"*30)

	for _ in range(5):
		print(choice(["apple", "banana", "pineapple"]))
	print("-"*30)

	print(shuffle(["apple", "banana", "pineapple"]))
	print("-"*30)

	for _ in range(5):
		print(randrange(0, 100))
	print("-"*30)

	for _ in range(5):
		print(nrandint(0, 100, 5))
	print("-"*30)

	for _ in range(5):
		print(nchoice(["apple", "banana", "pineapple"], 5))
	print("-"*30)