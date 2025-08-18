import sys

def get_value():
    if len(sys.argv) > 1:
        return sys.argv[1]
    else:
        print("No argument provided.")
        return None

if __name__ == "__main__":
    result = get_value()
    if result is not None:
        print(result)