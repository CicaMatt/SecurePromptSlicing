def write_to_file(filename, content):
    try:
        with open(filename, 'w') as file:
            file.write(content)
    except Exception as e:
        print(f"An error occurred: {e}")

filename = "example.txt"
content = "Hello, World!"
write_to_file(filename, content)