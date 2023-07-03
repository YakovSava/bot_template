from time import time
from rec import sorting_by_frequency as c_sorting_by_frequency

def timeit(func:callable):
    def wrapper(*args, **kwargs):
        start = time()
        func(*args, **kwargs)
        end = time()
        return end - start
    return wrapper

def py_sorting_by_frequency(lst):
    count_dict = {num: lst.count(num) for num in set(lst)}

    sorted_nums = sorted(count_dict.keys(), key=lambda x: count_dict[x], reverse=True)

    return sorted_nums

@timeit
def py_sorter():
    for _ in range(1000000):
        py_sorting_by_frequency([10, 0, 4, 9, 0, 0, 5, 0, 1, 2])

@timeit
def c_sorter():
    for _ in range(1000000):
        c_sorting_by_frequency([10, 0, 4, 9, 0, 0, 5, 0, 1, 2])

if __name__ == '__main__':
    print('Sorting by frequency 1 billion cycles Python: ', py_sorter())
    print('Sorting by frequency 1 billion cycles C++: ', c_sorter())