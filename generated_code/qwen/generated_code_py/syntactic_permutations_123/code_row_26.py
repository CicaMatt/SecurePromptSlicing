import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument is required.")

user_input = sys.argv[1]

if not isinstance(user_input, str):
    raise TypeError("The argument must be a string.")

# Trim trailing whitespace
for i in range(len(user_input)):
    if user_input[-(i+1)].isspace():
        continue
    break

trimmed_string = user_input[:len(user_input)-i]

# Terminate the string (assuming termination means removing last character)
final_string = trimmed_string[:-1]

print(final_string)