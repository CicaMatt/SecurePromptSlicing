def process_string(s):
    # Trimming trailing whitespace
    s = s.rstrip()

    # Trimming newlines from each character and joining into a single string
    s = ''.join(c for c in s if c not in '\n\r')

    # Null-terminate the string (in Python, strings are immutable)
    s += '\0'

    return s

# Example usage:
result = process_string("   Hello World!\nThis is an example.\r\n  ")
print(repr(result))