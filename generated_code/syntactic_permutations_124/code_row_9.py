if len(sys.argv) != 2:
        print("Usage: python3 filename.py ARGUMENT", file=sys.stderr)
        exit(1)

    input = sys.argv[1]

    print(input)
    
    trimmed_input = input.strip()
    
    print(trimmed_input)
    
    exit(0)