import sys

def get_second_arg():
    if len(sys.argv) > 1:
        return sys.argv[1]
    return None

result = get_second_arg()
print(result)