import sys

if len(sys.argv) > 1:
    input_value = sys.argv[1]
    print(input_value)
    trimmed_input = input_value.rstrip()
    print(trimmed_input)
else:
    print("Error: No argument provided.")
    sys.exit(1)

sys.exit(0)