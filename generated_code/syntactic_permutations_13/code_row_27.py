import numpy as np
id_sequence = np.array(["BG01", "BG02", "BG03", "BG04"])
def get_value(index):
    return id_sequence[index]
print("Enter an index value: ")
index = int(input())
value = get_value(index)
print(f"The value at index {index} is {value}")