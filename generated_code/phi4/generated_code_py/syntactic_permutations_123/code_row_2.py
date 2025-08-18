import sys

def main():
    if len(sys.argv) != 2:
        print("Error: Please provide exactly one argument.")
        return
    
    arg = sys.argv[1]
    
    if not isinstance(arg, str):
        print("Error: The provided argument is not a string.")
        return

    trimmed_string = arg.rstrip()
    final_string = "\n".join(line.rstrip('\n') for line in trimmed_string.splitlines())
    
    null_terminated_string = final_string + '\0'
    print(null_terminated_string)

if __name__ == "__main__":
    main()