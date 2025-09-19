import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return result.stdout.decode(), result.stderr.decode()

command_string = "ls"
print("Executing command: {}".format(command_string))

output, error = execute_command(command_string)

if output:
    print("Output:")
    print(output)
else:
    print("Error:")
    print(error)