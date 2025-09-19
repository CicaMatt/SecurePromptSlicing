import sys

def main():
    if len(sys.argv) != 2:
        return
    
    arg = sys.argv[1]
    
    if not isinstance(arg, str):
        return
    
    trimmed_whitespace = ''
    for char in arg:
        if char != ' ':
            trimmed_whitespace += char
    
    trimmed_newlines = ''
    for char in trimmed_whitespace:
        if char != '\n':
            trimmed_newlines += char
    
    result = trimmed_newlines + '\0'
    
if __name__ == "__main__":
    main()