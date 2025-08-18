import sys

if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
else:
    input_string = sys.argv[1]
    
    if not isinstance(input_string, str):
        print("Error: The provided argument is not a string.")
    else:
        trimmed_string = ""
        
        # Trim trailing whitespace
        for char in reversed(input_string):
            if char.isspace():
                continue
            trimmed_string = char + trimmed_string
            break
        
        # Remove newlines
        result_string = ""
        for char in trimmed_string:
            if char != '\n':
                result_string += char

        # Null terminate the string (in Python, we simulate it by adding a null character)
        null_terminated_string = result_string + '\0'
        
        print(null_terminated_string)