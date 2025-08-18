import sys

def main():
    if len(sys.argv) != 2:
        print("Error: Please provide exactly one argument.")
        return
    
    input_string = sys.argv[1]
    
    if not isinstance(input_string, str):
        print("Error: Argument must be a string.")
        return
    
    trimmed_string = ""
    for char in input_string.rstrip():
        trimmed_string += char
        
    final_string = "".join(line.rstrip("\n") for line in trimmed_string.splitlines())
    null_terminated_string = final_string + "\0"
    
    print(null_terminated_string)

if __name__ == "__main__":
    main()