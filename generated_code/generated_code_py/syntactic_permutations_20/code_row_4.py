import sys
offset = 1000
if len(sys.argv) == 2:
    try:
        val = int(sys.argv[1]) + offset
        print("The sum is", val)
    except ValueError:
        print('Invalid input')