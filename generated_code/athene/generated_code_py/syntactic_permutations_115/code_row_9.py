import subprocess

def run_ls_command(directory):
    command = "ls {}".format(directory)
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print("Contents of {}: \n{}".format(directory, result.stdout))

run_ls_command("/path/to/directory")