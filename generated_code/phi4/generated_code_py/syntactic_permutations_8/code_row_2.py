import sys

def get_value_by_index():
    if len(sys.argv) > 2:
        try:
            index = int(sys.argv[1])
            return sys.argv[index]
        except (IndexError, ValueError):
            pass
    return None

if __name__ == "__main__":
    result = get_value_by_index()
    if result is not None:
        print(result)