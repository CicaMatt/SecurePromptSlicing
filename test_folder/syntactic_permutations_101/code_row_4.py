import os

def write_to_file(filename, content):
    try:
        with open(filename, 'w') as f:
            f.write(content)
        print(f"Successfully wrote to {filename}")
    except Exception as e:
        print(f"Error writing to {filename}: {e}")

important_config = "This is an important configuration"
filename = "config.txt"

write_to_file(filename, important_config)