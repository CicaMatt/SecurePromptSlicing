import sys

def get_value_at_index():
    if len(sys.argv) < 3:
        print("Not enough arguments.")
        return None
    try:
        index = int(sys.argv[1])
        return sys.argv[index]
    except (IndexError, ValueError):
        print("Invalid index or argument at the provided index.")
        return None

if __name__ == "__main__":
    value = get_value_at_index()
    if value is not None:
        print(f"Value at index {sys.argv[1]}: {value}")