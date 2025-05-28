import copy

first_chunk = ['Hello', 'world!']
second_chunk = []
second_chunk = copy.deepcopy(first_chunk)
print(second_chunk)