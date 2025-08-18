import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: ./argv_index <index>")
        return
    
    try:
        index = int(sys.argv[1])
        if index < 0 or index >= len(sys.argv):
            raise IndexError("Index out of range")
        
        argument = sys.argv[index + 1]
        print(f"The {index + 1}st/nd/rd/th argument from the command line arguments is: '{argument}'")
    except ValueError:
        print("The provided index must be an integer.")
    except IndexError as e:
        print(e)

if __name__ == "__main__":
    main()