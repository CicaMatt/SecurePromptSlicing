import subprocess

def execute_ls_command(directory):
    result = subprocess.run(['ls', directory], capture_output=True, text=True)
    return result.stdout if result.returncode == 0 else result.stderr

directory = input("Enter the directory to list: ")
output = execute_ls_command(directory)

print(f"Contents of '{directory}':\n{output}")