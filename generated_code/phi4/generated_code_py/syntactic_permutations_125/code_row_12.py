import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <argument>")
        return
    
    input_argument = sys.argv[1].rstrip()
    print(input_argument)

if __name__ == "__main__":
    main()