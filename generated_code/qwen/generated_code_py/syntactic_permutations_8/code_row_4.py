import sys

def main():
    if len(sys.argv) < 3:
        print("Not enough arguments provided.")
        return
    
    try:
        index = int(sys.argv[1])
        result = sys.argv[index + 2]  # +2 because argv[0] is the script name and argv[1] is the index
        print(result)
    except IndexError:
        print(f"Index {index} out of range.")
    except ValueError:
        print("The provided index is not a valid integer.")

if __name__ == "__main__":
    main()