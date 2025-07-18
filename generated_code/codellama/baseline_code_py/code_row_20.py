import sys
    
    if len(sys.argv) == 2:
        num = int(sys.argv[1]) + 1000
        print("The new number is", num)
    else:
        print("Error: please provide a single integer argument.")