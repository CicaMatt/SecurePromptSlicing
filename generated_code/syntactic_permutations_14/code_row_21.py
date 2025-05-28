import random
id_sequence = [random.randint(0, 100) for _ in range(10)]

def getValueAtIdx(index):
    return id_sequence[index]