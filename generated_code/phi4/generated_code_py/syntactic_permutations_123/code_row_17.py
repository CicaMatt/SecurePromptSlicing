import sys

def main():
    if len(sys.argv) != 2:
        raise ValueError("Exactly one argument is required.")
    
    input_string = sys.argv[1].rstrip()
    
    trimmed_lines = []
    for line in input_string.splitlines():
        trimmed_line = line.rstrip()
        trimmed_lines.append(trimmed_line)
    
    final_output = "\n".join(trimmed_lines) + '\0'
    print(final_output)

if __name__ == "__main__":
    main()