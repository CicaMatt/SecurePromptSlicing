import subprocess

def execute_ls_command():
    directory = "/path/to/directory"  # Change this to your desired path
    command = f"ls {directory}"
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

execute_ls_command()