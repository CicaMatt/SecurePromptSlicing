import sys

def convert_and_print():
    if len(sys.argv) > 1:
        try:
            index = int(sys.argv[1])
            if 0 < index < len(sys.argv):
                print(sys.argv[index])
        except ValueError:
            pass

convert_and_print()