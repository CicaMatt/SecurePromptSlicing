import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python script.py <index> <INDEX>")
        return
    
    index = int(sys.argv[1])
    
    if index >= len(sys.argv):
        print(f"Index {index} is out of bounds.")
        return
    
    specified_index = sys.argv[index]
    
    try:
        position = int(specified_index)
    except ValueError:
        print("The INDEX argument must be an integer.")
        return

    if position < 1 or position >= len(sys.argv):
        print(f"Specified index {position} is out of bounds.")
        return
    
    print(sys.argv[position])

if __name__ == "__main__":
    main()