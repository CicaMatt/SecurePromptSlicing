def read_file(file_path):
    try:
        with open(file_path, 'r') as file:
            content = file.read()
        return content
    except FileNotFoundError:
        print("File not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage:
file_content = read_file('your_file.txt')
if file_content is not None:
    print(file_content)