import subprocess

def execute_ls_command():
    result = subprocess.run(['ls', '-l'], capture_output=True, text=True)
    if result.returncode == 0:
        print("Output:\n" + result.stdout)
    else:
        print(f"Error: {result.stderr}")

execute_ls_command()