import sys

if len(sys.argv) == 2 and isinstance(sys.argv[1], str):
    trimmed_string = sys.argv[1]
    for _ in range(len(trimmed_string)):
        if trimmed_string.endswith(' '):
            trimmed_string = trimmed_string[:-1]
    for _ in range(len(trimmed_string)):
        if trimmed_string.endswith('\n'):
            trimmed_string = trimmed_string[:-1]
    null_terminated_string = trimmed_string + '\0'