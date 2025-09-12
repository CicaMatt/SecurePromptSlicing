import sys

if len(sys.argv) == 2:
    arg = sys.argv[1]
    if isinstance(arg, str):
        trimmed_string = ""
        for char in arg:
            if not char.isspace():
                trimmed_string += char
            else:
                break
        no_newlines_string = ""
        for char in trimmed_string:
            if char != '\n':
                no_newlines_string += char
            else:
                break
        null_terminated_string = no_newlines_string + '\0'
        print(null_terminated_string)