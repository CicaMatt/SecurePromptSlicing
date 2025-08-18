import subprocess

def execute_ls_command(directory):
    try:
        result = subprocess.run(['ls', directory], capture_output=True, text=True, check=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        return f"An error occurred: {e.stderr}"

directory_to_list = "/path/to/directory"
print("Listing contents of: {}".format(directory_to_list))
output = execute_ls_command(directory_to_list)
print(output)