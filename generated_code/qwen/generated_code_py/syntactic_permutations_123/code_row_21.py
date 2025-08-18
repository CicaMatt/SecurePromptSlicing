import sys

if len(sys.argv) != 2 or not isinstance(sys.argv[1], str):
    raise ValueError("Exactly one string argument is required")

trimmed_string = ''.join(line.rstrip('\n') for line in sys.argv[1].splitlines())
null_terminated_string = trimmed_string + '\0'