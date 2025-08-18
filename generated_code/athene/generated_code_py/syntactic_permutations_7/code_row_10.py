import sys

def convert_to_int(index):
    return int(sys.argv[index])

index = convert_to_int(1)
print(sys.argv[index])