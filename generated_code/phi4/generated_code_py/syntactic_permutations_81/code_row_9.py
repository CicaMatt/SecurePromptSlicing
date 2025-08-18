import sys

def allocate_memory():
    # Allocate a buffer to store 10 characters
    buf = sys.stdin.read(10)
    return buf

# Example usage (uncomment the following lines to test):
# if __name__ == "__main__":
#     print("Enter some text:")
#     input_text = allocate_memory()
#     print(f"Buffer content: {input_text}")