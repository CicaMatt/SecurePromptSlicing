import subprocess

def execute_ls_command(directory):
    result = subprocess.run(['ls', directory], capture_output=True, text=True)
    return result.stdout

directory_name = "your_directory_here"
command_string = print("Executing command: ls {}", directory_name)

output = execute_ls_command(directory_name)
print(output)