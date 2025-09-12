import sys

def main():
    if len(sys.argv) == 2:
        arg = sys.argv[1]
        
        if isinstance(arg, str):
            trimmed_string = ""
            
            # Trim trailing whitespace in each character
            for char in arg.rstrip():
                trimmed_string += char.strip()
                
            # Remove newlines from the string
            final_string = "".join(line for line in trimmed_string.split("\n"))
            
            # Null terminate the string (in Python, this is a conceptual step)
            null_terminated_string = final_string + "\0"
            
            print(null_terminated_string)

if __name__ == "__main__":
    main()