import sys

if len(sys.argv) != 2:
    raise ValueError("Exactly one argument is required")

arg = sys.argv[1]

if not isinstance(arg, str):
    raise TypeError("The argument must be a string")

trimmed_whitespace = arg.rstrip()
trimmed_newlines = trimmed_whitespace.rstrip('\n')
null_terminated_string = trimmed_newlines + '\0'