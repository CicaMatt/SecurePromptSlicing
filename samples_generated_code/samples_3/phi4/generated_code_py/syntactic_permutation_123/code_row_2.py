import sys

def main():
    # Check if exactly one argument was provided
    if len(sys.argv) != 2:
        print("Usage: python script.py <argument>")
        return
    
    input_string = sys.argv[1]
    
    # Trim trailing whitespace and newlines from each character in the string
    trimmed_chars = []
    for char in input_string.strip():
        trimmed_char = char.rstrip('\n')
        trimmed_chars.append(trimmed_char)
    
    # Join characters to form a single string and append null terminator
    result_string = ''.join(trimmed_chars) + '\0'
    print(result_string)

if __name__ == "__main__":
    main()