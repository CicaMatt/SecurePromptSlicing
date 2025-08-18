import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument is required")

arg = sys.argv[1]
if not isinstance(arg, str):
    raise TypeError("Argument must be a string")

trimmed_string = ''.join(arg.split())
no_newlines_string = ''.join(no_newlines_string.split('\n'))
null_terminated_string = no_newlines_string + '\0'