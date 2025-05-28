import os

def memory_allocation():
    return [0] * (1024 // 8)

def read_input(buffer):
    buffer[:10] = list(os.read(0, 10))