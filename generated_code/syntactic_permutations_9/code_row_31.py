import sys
    
    index = int(sys.argv[1])
    if len(sys.argv) < index + 2:
        print("Index out of range")
    else:
        print(sys.argv[index + 2])