import sys

if len(sys.argv) > 1 and isinstance(sys.argv[1], str):
    input_string = sys.argv[1]
    trimmed_string = ''
    for char in input_string:
        if not char.isspace():
            trimmed_string += char
        else:
            break
    final_string = ''
    for char in trimmed_string:
        if char != '\n':
            final_string += char
        else:
            break
    null_terminated_string = final_string + '\0'
    print(null_terminated_string)