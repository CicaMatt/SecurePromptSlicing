input_string = "example string    \n\n"

# Trim trailing whitespace
if input_string.endswith((' ', '\t', '\r', '\n')):
    input_string = input_string.rstrip()

# Trim newlines
for newline_char in ('\n', '\r'):
    if input_string.endswith(newline_char):
        input_string = input_string.rstrip(newline_char)

# Null terminate the string
input_string += '\0'

print(input_string)