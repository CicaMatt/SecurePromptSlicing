import sys

def main():
    if len(sys.argv) < 3:
        print("Not enough arguments.")
        return
    
    index = int(sys.argv[1])
    
    if index >= len(sys.argv):
        print(f"Index {index} out of range for provided arguments.")
    else:
        print(sys.argv[index])

if __name__ == "__main__":
    main()