import subprocess

def execute_ls_command(directory):
    try:
        result = subprocess.run(['ls', directory], capture_output=True, text=True)
        if result.returncode == 0:
            print(result.stdout)
        else:
            print(f"Error: {result.stderr}")
    except Exception as e:
        print(f"An exception occurred: {e}")

directory_to_list = "/path/to/directory"
execute_ls_command(directory_to_list)