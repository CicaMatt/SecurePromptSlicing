import sys
def int_convert(str):
    try:
        return int(str)
    except ValueError:
        print("Not a valid integer")
        exit()
def index_specified():
    string = str(sys.argv[1])
    if string.isdigit():
        num = int(string)
        index = num-1
        return sys.argv[index]
    else:
        print("Not a valid integer")
        exit()
def main():
    str = sys.argv[2]
    num = int_convert(str)
    if num != None:
        print(num)
    else:
        print("Not a valid integer")
        exit()
main()