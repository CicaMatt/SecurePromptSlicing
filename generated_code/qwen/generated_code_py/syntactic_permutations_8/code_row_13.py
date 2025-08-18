import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> arg1 arg2 ...")
        return
    
    try:
        index = int(sys.argv[1])
        result = sys.argv[index + 1]
        print(result)
    except IndexError:
        print(f"Index {index} is out of range for the provided arguments.")
    except ValueError:
        print("Please provide a valid integer as the index.")

if __name__ == "__main__":
    main()