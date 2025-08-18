import subprocess

def run_ls_command(directory):
    command = f"ls {directory}"
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result.stdout)

run_ls_command('/path/to/directory')