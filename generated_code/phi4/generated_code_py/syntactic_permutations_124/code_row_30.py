import sys

if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
    sys.exit(1)

user_input = sys.argv[1]
print(user_input)
trimmed_input = user_input.strip()
print(trimmed_input)
sys.exit(0)