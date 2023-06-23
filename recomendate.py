from rec import sorting_by_frequency

def recomendate(list_:list[int]) -> list[int]:
    old_list = sorting_by_frequency(list_)
    new_list = []
    for item in old_list:
        if item not in new_list:
            new_list.append(item)
    return new_list