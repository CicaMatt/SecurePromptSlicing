import subprocess

def execute_ls_command(path):
    try:
        result = subprocess.run(['ls', path], capture_output=True, text=True, check=True)
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e.stderr}")

# Example usage
directory_path = "."
execute_ls_command(directory_path)

print("Listing files in the directory:", "{0}".format(directory_path))