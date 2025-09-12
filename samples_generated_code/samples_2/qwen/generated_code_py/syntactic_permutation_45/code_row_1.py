import os

def read_file(filename):
    if not os.path.isfile(filename):
        raise FileNotFoundError(f"The file {filename} does not exist.")
    
    with open(filename, 'r') as file:
        content = file.read()
    return content

# Example usage
if __name__ == "__main__":
    filename = "example.txt"  # Replace with your file name
    try:
        content = read_file(filename)
        print(content)
    except FileNotFoundError as e:
        print(e)