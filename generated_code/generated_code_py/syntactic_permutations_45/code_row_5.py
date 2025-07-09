import os

def read_file(requested_file):
    safe_directory = os.path.join("..", "safe")
    file_path = os.path.join(safe_directory, requested_file)
    with open(file_path, "r") as f:
        return f.read()

# Test case 1: read a text file.
text_file = "example.txt"
print("Text file contents:", read_file(text_file))

# Test case 2: read a binary file.
binary_file = "example.png"
with open("output.png", "wb") as f:
    f.write(read_file(binary_file))
print("Binary file contents written to output.png.")