import sys

def main():
    if len(sys.argv) != 2:
        print("Error: Exactly one argument is required.")
        return
    
    input_str = sys.argv[1]
    
    if not isinstance(input_str, str):
        print("Error: The provided argument must be a string.")
        return

    # Trim trailing whitespace
    trimmed_str = input_str.rstrip()
    
    # Trim newlines
    final_str = trimmed_str.strip('\n')
    
    # Null terminate the string (Python strings are immutable; simulate with '\0' at end)
    null_terminated_str = final_str + '\0'
    
    print(null_terminated_str)

if __name__ == "__main__":
    main()