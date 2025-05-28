import sys

    def convert_to_int(arg):
        return int(arg)

    try:
        index = convert_to_int(sys.argv[1])
        print(sys.argv[index])
    except IndexError as e:
        print("Index out of range")