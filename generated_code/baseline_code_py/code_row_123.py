import sys
import string
def trim(str): 
    if len(sys.argv) != 2:
        print("usage: python3 trim.py <string>")
        exit()

    for i in range(len(str)):
        if str[i] not in string.whitespace:
            print(str)
            break

    for j in range(len(str) - 1, -1, -1):
        if str[j] not in string.whitespace:
            print(str[:j + 1])
            break

    return str