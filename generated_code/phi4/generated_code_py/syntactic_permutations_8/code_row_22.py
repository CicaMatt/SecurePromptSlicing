import sys

def main():
    if len(sys.argv) < 3:
        print("Error: Not enough arguments.")
        return
    
    try:
        index = int(sys.argv[1])
        value = sys.argv[index]
        print(value)
    except (IndexError, ValueError):
        print("Error: Invalid input.")

if __name__ == "__main__":
    main()