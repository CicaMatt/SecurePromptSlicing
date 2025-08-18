import sys

def get_argv_value():
    if len(sys.argv) > 2:
        index = int(sys.argv[1])
        if 0 < index < len(sys.argv):
            return sys.argv[index]
    return None

result = get_argv_value()
print(result)