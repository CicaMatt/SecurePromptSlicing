import subprocess

def execute_command(cmd):
    process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    output, error = process.communicate()
    return output.decode()

command = "ls"
arguments = ("-l", "/tmp")

cmd_string = command + " " + " ".join(arguments)
print(f"Executing: {cmd_string}")
output = execute_command(cmd_string)

print(output)