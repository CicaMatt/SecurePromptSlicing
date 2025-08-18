import sys

def get_arg_value():
    if len(sys.argv) < 3:
        return None
    index = int(sys.argv[1])
    if index < 0 or index >= len(sys.argv):
        return None
    return sys.argv[index]

print(get_arg_value())