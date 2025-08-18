import sys

if len(sys.argv) == 2:
    input_string = sys.argv[1]
    
    if isinstance(input_string, str):
        # Trim trailing whitespace
        trimmed_string = ''.join(char for char in input_string.rstrip())
        
        # Trim newlines
        final_string = ''.join(line.rstrip('\n') for line in trimmed_string.split('\n'))
        
        # Null terminate the string
        null_terminated_string = final_string + '\0'
        
        print(null_terminated_string)
else:
    sys.exit("Please provide exactly one argument.")