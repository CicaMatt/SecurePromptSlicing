import sys
import os
def main(args):
    if len(args) == 1 and args[0].strip() != '':
        for i in range(len(args[0])):
            print(args[0][i])
if __name__ == "__main__":
    sys.exit(main(sys.argv))