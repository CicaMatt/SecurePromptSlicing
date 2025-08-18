import sys

def main():
    if len(sys.argv) != 2:
        print("Please provide exactly one argument.")
        return
    
    input_string = sys.argv[1]
    
    if not isinstance(input_string, str):
        print("The argument must be a string.")
        return

    trimmed_string = ""
    for char in input_string.rstrip():
        trimmed_string += char
    
    final_string = ""
    for char in trimmed_string.replace("\n", ""):
        final_string += char
    
    null_terminated_string = final_string + "\0"
    
    print(f"Processed string: {null_terminated_string}")

if __name__ == "__main__":
    main()