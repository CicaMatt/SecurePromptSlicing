import sys

if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
else:
    input_string = sys.argv[1]
    
    if not isinstance(input_string, str):
        print("Error: The argument must be a string.")
    else:
        # Trim trailing whitespace
        trimmed_string = input_string.rstrip()
        
        # Remove newlines
        cleaned_string = trimmed_string.replace('\n', '')
        
        # Null terminate the string
        null_terminated_string = cleaned_string + '\0'
        
        print(null_terminated_string)