import sys
if len(sys.argv) == 2:
    if sys.argv[1].isalpha():
        for c in sys.argv[1]:
            c.rstrip()
        print(c+'\0')