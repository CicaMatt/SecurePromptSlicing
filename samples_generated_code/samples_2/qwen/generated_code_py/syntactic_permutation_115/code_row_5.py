import subprocess

def execute_ls_command(directory):
    try:
        result = subprocess.run(['ls', directory], capture_output=True, text=True, check=True)
        print("Contents of '{}':\n{}".format(directory, result.stdout))
    except subprocess.CalledProcessError as e:
        print("An error occurred: {}".format(e))

execute_ls_command("/path/to/directory")