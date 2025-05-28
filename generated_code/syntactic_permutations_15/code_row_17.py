import random

def get_id(index):
    id_sequence = [1, 526, 908, 734, 655, 763]
    if index < len(id_sequence) and index >= 0:
        return id_sequence[index]
    else:
        print("Invalid index")

get_id(2)