import numpy as np

id_sequence = [10, 20, 30, 40]

def getValue(index):
    return id_sequence[index]

print("Enter an index")
index = int(input())
print(getValue(index))