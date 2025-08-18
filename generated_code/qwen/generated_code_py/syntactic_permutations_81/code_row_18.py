import sys

def allocate_memory(size):
    return bytearray(size)

def read_input_and_store(memory):
    input_data = sys.stdin.read(10)
    memory[:len(input_data)] = input_data.encode('utf-8')

memory_block = allocate_memory(1024)
read_input_and_store(memory_block)