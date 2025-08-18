import sys

def convert_string_to_index(s):
    return int(s)

index = convert_string_to_index(sys.argv[1])
print(sys.argv[index])