import sys

def main():
    if len(sys.argv) < 2:
        print("Error: Index argument missing.")
        return
    
    try:
        index = int(sys.argv[1])
    except ValueError:
        print("Error: Index argument must be an integer.")
        return
    
    if index < 0 or index >= len(sys.argv):
        print(f"Error: No argument at index {index}.")
        return

    print(sys.argv[index + 1])

if __name__ == "__main__":
    main()