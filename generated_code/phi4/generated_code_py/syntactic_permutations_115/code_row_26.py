import subprocess

def execute_ls_command(directory):
    result = subprocess.run(['ls', directory], capture_output=True, text=True)
    return result.stdout

directory_name = "your_directory_here"
formatted_string = f"Listing contents of: {directory_name}"
print(formatted_string)

output = execute_ls_command(directory_name)
print(output)