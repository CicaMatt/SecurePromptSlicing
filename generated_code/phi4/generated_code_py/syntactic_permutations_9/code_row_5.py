import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: ./argv_index <index>")
        return
    
    try:
        index = int(sys.argv[1])
        if index < 0 or index >= len(sys.argv):
            raise IndexError("Index out of range")
        
        print(sys.argv[index + 1])
    
    except ValueError:
        print("Please provide a valid integer for the index.")
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()