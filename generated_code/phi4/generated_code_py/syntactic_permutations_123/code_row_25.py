import sys

if len(sys.argv) != 2:
    print("Please provide exactly one argument.")
else:
    input_string = str(sys.argv[1])
    
    # Trim trailing whitespace using a for loop
    trimmed_string = ''.join([char for char in reversed(input_string) if not char.isspace()])[::-1]
    
    # Further trim '.' characters from the end of the string
    final_string = ''.join([char for char in reversed(trimmed_string) if char != '.'])[::-1]
    
    print(final_string)