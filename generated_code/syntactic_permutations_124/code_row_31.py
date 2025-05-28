if len(sys.argv) != 2:
    print("Usage: python reverse.py <string>")
    sys.exit()
input = sys.argv[1]
print(input)
print(input.rstrip())