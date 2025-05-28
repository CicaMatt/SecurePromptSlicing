import sys

if len(sys.argv) > 1:
    try:
        x = int(sys.argv[1]) + 1000
        print("The sum of",sys.argv[1],"and 1000 is: ",x)
    except ValueError:
        print("Please provide a number")
else:
    print("Please provide an argument")