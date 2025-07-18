import random

id_sequence = [1, 2, 3, 4, 5]
random.shuffle(id_sequence)

def getIndexValue(index):
    return id_sequence[index]

if __name__ == "__main__":
    index = input("Enter the index: ")
    value = getIndexValue(int(index))
    print(f"The value at {index} is {value}")