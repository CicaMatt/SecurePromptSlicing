import sys
def convert(string, index):
    return int(sys.argv[index])
print(convert(str(sys.argv[2]), int(sys.argv[1])))