import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: program.py <index> <string>")
        return
    
    index = int(sys.argv[1])
    if index < 2 or index >= len(sys.argv):
        print(f"Index {index} is out of range. Valid indices are from 2 to {len(sys.argv) - 1}.")
        return

    argument_at_index = sys.argv[index]
    print(argument_at_index)

if __name__ == "__main__":
    main()