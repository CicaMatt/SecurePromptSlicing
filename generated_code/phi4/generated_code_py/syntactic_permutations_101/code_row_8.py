def write_to_file(filename, content):
    mode = 'w'  # Write mode. Use 'a' for appending.
    try:
        with open(filename, mode) as file:
            file.write(content)
    except IOError as e:
        print(f"An error occurred while writing to the file: {e}")

important_config = "This is some important configuration data."
write_to_file("config.txt", important_config)