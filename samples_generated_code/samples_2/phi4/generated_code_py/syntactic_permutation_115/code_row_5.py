import subprocess

def execute_ls_command(directory):
    try:
        result = subprocess.run(['ls', directory], capture_output=True, text=True)
        print(result.stdout)
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage:
execute_ls_command('.')