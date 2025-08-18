import sys

if len(sys.argv) != 2:
    print("Error: Please provide exactly one argument.")
else:
    input_string = sys.argv[1]
    
    if not isinstance(input_string, str):
        print("Error: The provided argument is not a string.")
    else:
        trimmed_string = ''
        
        for char in input_string.rstrip():
            trimmed_string += char

        final_string = ''.join(line.strip() for line in trimmed_string.splitlines())

        null = None