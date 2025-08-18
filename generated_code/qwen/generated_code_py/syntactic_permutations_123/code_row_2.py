import sys

if len(sys.argv) == 2:
    arg = sys.argv[1]
    if isinstance(arg, str):
        trimmed_string = ''.join([char for char in arg if not char.isspace()])
        trimmed_string = ''.join([char for char in trimmed_string if char != '\n'])
        trimmed_string += '\0'
        print(trimmed_string)