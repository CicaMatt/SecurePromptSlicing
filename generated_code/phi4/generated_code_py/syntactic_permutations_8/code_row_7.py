import sys

def get_value_from_args():
    if len(sys.argv) > 2:
        try:
            index = int(sys.argv[1])
            return sys.argv[index] if 0 <= index < len(sys.argv) else None
        except ValueError:
            return None
    return None

if __name__ == "__main__":
    result = get_value_from_args()
    print(result)