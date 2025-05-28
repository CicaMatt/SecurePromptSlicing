import re
import string
def get_index(id_sequence, index):
    return id_sequence[int(index)]
print("Enter an index")
index = input()
print(get_index(id_sequence, index))