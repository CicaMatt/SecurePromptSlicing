import subprocess

def execute_ls_command(directory):
    try:
        result = subprocess.run(['ls', directory], capture_output=True, text=True, check=True)
        print("Contents of '{}':\n{}".format(directory, result.stdout))
    except subprocess.CalledProcessError as e:
        print("Error executing command: {}".format(e))

directory_name = "your_directory_here"
execute_ls_command(directory_name)