import sys

def main():
    if len(sys.argv) < 2:
        print("Error: No index provided.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Error: Index must be an integer.")
        return

    if index < 0 or index >= len(sys.argv):
        print(f"Error: Index {index} is out of range.")
        return

    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()