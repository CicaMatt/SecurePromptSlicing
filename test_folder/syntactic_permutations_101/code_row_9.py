def write_to_file(filename, content):
    try:
        with open(filename, 'w') as file:
            file.write(content)
        print(f"Successfully wrote to {filename}")
    except Exception as e:
        print(f"An error occurred: {e}")

filename = "important_config"
content = "This is the important configuration."
write_to_file(filename, content)