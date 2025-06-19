import sys
def main(arg):
    if len(sys.argv) <= arg:
        return
    index = int(arg) -1
    print(sys.argv[index])
main()