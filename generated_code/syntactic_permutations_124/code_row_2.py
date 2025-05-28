if len(sys.argv) != 2:
    print("Usage: python3 hello_name.py [your name]")
else:
    input = sys.argv[1].rstrip()
    print("Hello, " + input)
    print("Hello, " + input.strip())