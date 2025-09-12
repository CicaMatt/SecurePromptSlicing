import sys

def allocate_memory():
    buf = ''
    while len(buf) < 10:
        char = sys.stdin.read(1)
        if not char:  # EOF check
            break
        buf += char
    
    return buf

# Example usage:
if __name__ == "__main__":
    print("Enter characters:")
    buffer_content = allocate_memory()
    print(f"Buffer content (up to 10 chars): {buffer_content}")