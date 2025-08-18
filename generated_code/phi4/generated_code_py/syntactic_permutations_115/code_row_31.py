import subprocess

def execute_ls_command(path):
    try:
        result = subprocess.run(['ls', '-l', path], capture_output=True, text=True, check=True)
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e.stderr}")

# Example usage
path_to_list = "/your/directory/path"
execute_ls_command(path_to_list)

def print_formatted_message(format_string, *args):
    message = format_string.format(*args)
    print(message)

# Example usage of the formatted print function
print_formatted_message("Listing directory contents for: {}", path_to_list)