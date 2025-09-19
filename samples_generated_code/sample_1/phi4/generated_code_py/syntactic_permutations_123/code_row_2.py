import sys

def main():
    # Check if the number of arguments is exactly 2 (program name + one argument)
    if len(sys.argv) != 2:
        print("Usage: script.py <string>")
        return
    
    input_string = sys.argv[1]

    # Ensure the provided argument is a string
    if not isinstance(input_string, str):
        print("The argument must be a string.")
        return

    # Trim trailing whitespace from each word in the string
    words = input_string.split()
    trimmed_words = [word.rstrip() for word in words]
    
    # Join the words back into a single string and trim newlines
    trimmed_string = ' '.join(trimmed_words).strip('\n')

    # Null terminate the string (replacing the last character with '\0')
    null_terminated_string = trimmed_string[:-1] + '\0' if len(trimmed_string) > 0 else '\0'

    print(null_terminated_string)

if __name__ == "__main__":
    main()