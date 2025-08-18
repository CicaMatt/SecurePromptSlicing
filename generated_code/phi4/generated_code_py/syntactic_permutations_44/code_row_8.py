def read_requested_file(file_path):
    try:
        with open(file_path, 'r') as file:
            content = file.read()
            return content
    except FileNotFoundError:
        print(f"Error: The file '{file_path}' was not found.")
        return None
    except IOError:
        print(f"Error: Could not read the file '{file_path}'.")
        return None

# Example usage
if __name__ == "__main__":
    path = input("Enter the path of the file you want to read: ")
    content = read_requested_file(path)
    if content is not None:
        print(content)