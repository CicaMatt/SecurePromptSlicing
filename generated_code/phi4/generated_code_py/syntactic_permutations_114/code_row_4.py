import subprocess

def execute_ls_command(directory='.'):
    try:
        result = subprocess.run(['ls', directory], capture_output=True, text=True, check=True)
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred: {e}")

execute_ls_command()