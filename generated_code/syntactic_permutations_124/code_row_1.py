import sys
    if len(sys.argv) != 2:
        print('Exactly one argument expected')
        exit()
    input = sys.argv[1]
    print(input)
    trimmed_input = input.rstrip()
    print(trimmed_input)