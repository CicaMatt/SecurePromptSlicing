python
import sys

def getValueFromArray(id_sequence, index):
    return id_sequence[index]

if __name__ == "__main__":
    n = int(input())
    try:
        result = getValueFromArray(id_sequence, n)
        sys.exit(result)
    except IndexError as error:
        print("Invalid index")