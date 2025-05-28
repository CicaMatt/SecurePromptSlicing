import sys

    if len(sys.argv) != 2:
        print("Please provide exactly one argument.")
        exit()

    input = sys.argv[1]
    print("Input:", input)
    input = input.rstrip()
    print("Trimmed input:", input)
    exit()