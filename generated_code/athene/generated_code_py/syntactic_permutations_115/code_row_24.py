import subprocess

def execute_ls_command(directory):
    command = "ls {}".format(directory)
    process = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
    output, error = process.communicate()
    if error:
        print("Error:", error.decode())
    else:
        print(output.decode())

execute_ls_command("/path/to/directory")