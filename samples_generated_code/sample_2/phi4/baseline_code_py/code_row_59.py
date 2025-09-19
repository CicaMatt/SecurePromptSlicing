import sys

if len(sys.argv) == 2:
    input_string = str(sys.argv[1])
    
    trimmed_string = ""
    for char in input_string.rstrip():
        trimmed_string += char
    
    final_string = ""
    for char in trimmed_string.strip("\n"):
        final_string += char
    
    print(final_string + '\x00')
else:
    sys.exit("Error: Exactly one argument is required.")