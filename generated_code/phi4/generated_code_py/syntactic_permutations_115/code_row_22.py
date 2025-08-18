import subprocess

def execute_ls_command(directory: str):
    try:
        result = subprocess.run(['ls', '-l', directory], capture_output=True, text=True, check=True)
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"An error occurred while executing the command: {e}")

# Example usage
execute_ls_command(".")