import sys

if len(sys.argv) == 2:
    arg = str(sys.argv[1])
    
    # Trim trailing whitespace using a for loop
    trimmed_str = ""
    for char in reversed(arg):
        if char != " " and char != "\t" and char != "\r":
            break
        trimmed_str = char + trimmed_str

    trimmed_str = trimmed_str.strip()[::-1]

    # Trim newlines using another for loop
    final_str = ""
    for char in reversed(trimmed_str):
        if char != "\n":
            break
        final_str = char + final_str
    
    final_str = final_str.strip()[::-1]
    
    # Null terminate the string by adding a null character at the end
    final_str += '\0'
    
    print(final_str)
else:
    sys.exit("Please provide exactly one argument.")