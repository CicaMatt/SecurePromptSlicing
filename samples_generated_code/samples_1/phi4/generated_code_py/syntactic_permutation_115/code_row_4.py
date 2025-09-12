import subprocess

def execute_command(command: str):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    if result.returncode == 0:
        print(result.stdout)
    else:
        print(f"Error: {result.stderr}")

command_template = "ls {directory}"
print("Enter the directory to list:")
directory_input = input()
execute_command(command_template.format(directory=directory_input))