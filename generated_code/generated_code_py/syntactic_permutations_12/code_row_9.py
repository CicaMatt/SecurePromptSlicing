import sys

def getValueFromArray(arr,index):
    try:
        if index < 0 or index >= len(arr):
            raise ValueError()
        else:
            return arr[index]
    except ValueError as e:
        print("Index out of bound")
        sys.exit(-1)
    except Exception as e:
        print("Invalid argument")
        sys.exit(-2)
    
def main():
    try:
        index = int(input())
        arr = [0,1,2,3]
        value = getValueFromArray(arr,index)
        print(value)
        sys.exit(value)
    except ValueError as e:
        print("Invalid argument")
        sys.exit(-3)
    except Exception as e:
        print("Unexpected error")
        sys.exit(-4)
    
if __name__ == "__main__":
    main()