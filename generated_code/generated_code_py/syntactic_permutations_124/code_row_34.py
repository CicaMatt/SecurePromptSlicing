import sys

if len(sys.argv) != 2:
    print("Usage: python <script> input")
    exit()

input = sys.argv[1]
print(input)

trimmed_input = input.rstrip()
print(trimmed_input)