import subprocess

def execute_command(command):
    process = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    output, error = process.communicate()
    return output.decode()

def ls(directory):
    command = "ls {}".format(directory)
    result = execute_command(command)
    print(result)

directory = "/path/to/directory"
ls(directory)