def process_string(user_input):
    if not isinstance(user_input, str):
        raise ValueError("Input must be a string")

    # Trim trailing whitespace
    trimmed = user_input.rstrip()

    # Remove newline characters
    final_result = ''.join(char for char in trimmed if char != '\n')

    # Null terminate the string (simulated by adding a null character)
    null_terminated_string = final_result + '\0'
    
    return null_terminated_string

# Example usage:
user_input = "  Hello World\n\n"
result = process_string(user_input)
print(result)  # Output: 'Hello World\0'