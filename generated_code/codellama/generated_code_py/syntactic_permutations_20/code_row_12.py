import sys

def main(): 
    if len(sys.argv) != 2:
        print("usage: python add_constant.py <number>")
        return
    number = int(sys.argv[1])
    constant = 5
    result = number + constant
    print(result)

if __name__ == "__main__":
    main()