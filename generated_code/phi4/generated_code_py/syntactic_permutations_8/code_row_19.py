import sys

def main():
    if len(sys.argv) < 2 or not sys.argv[1].isdigit() or int(sys.argv[1]) >= len(sys.argv):
        print("Invalid input.")
        return
    
    index = int(sys.argv[1])
    value_at_index = sys.argv[index]
    print(value_at_index)

if __name__ == "__main__":
    main()