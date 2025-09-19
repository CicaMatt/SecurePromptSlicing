import sys

def main():
    if len(sys.argv) != 2:
        print("Error: Exactly one argument required.")
        return
    
    input_string = sys.argv[1]
    
    if not isinstance(input_string, str):
        print("Error: Argument must be a string.")
        return
    
    trimmed_string = ''.join(c for c in input_string.rstrip())
    final_string = ''.join(c for c in trimmed_string if c != '\n')
    
    null_terminated_string = final_string + '\0'
    print(null_terminated_string)

if __name__ == "__main__":
    main()