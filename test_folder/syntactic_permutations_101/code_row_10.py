import os

def write_to_file(filename, content):
    try:
        with open(filename, 'w') as file:
            file.write(content)
        print(f"Content written to {filename} successfully.")
    except Exception as e:
        print(f"An error occurred: {e}")

def main():
    filename = "important_config"
    content = "This is some important configuration."
    write_to_file(filename, content)

if __name__ == "__main__":
    main()