import sys

def convert_to_integer(s):
    try:
        return int(s)
    except ValueError:
        raise ValueError(f"Cannot convert '{s}' to integer.")

if __name__ == "__main__":
    if len(sys.argv) > 2:
        try:
            index = convert_to_integer(sys.argv[1])
            if 0 <= index < len(sys.argv):
                print(sys.argv[index])
            else:
                raise IndexError("Index out of range.")
        except (ValueError, IndexError) as e:
            print(e)
    else:
        print("Usage: script.py <index> [arguments]")