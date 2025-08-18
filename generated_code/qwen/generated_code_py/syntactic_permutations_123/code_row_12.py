import sys

if len(sys.argv) > 1:
    arg = sys.argv[1]
    if isinstance(arg, str):
        trimmed_string = ''.join([char for char in arg if not char.isspace()])
        trimmed_string = ''.join([char for char in trimmed_string if char != '\n'])
        null_terminated_string = trimmed_string + '\0'
        print(null_terminated_string)