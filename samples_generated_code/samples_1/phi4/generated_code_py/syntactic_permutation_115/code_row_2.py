import subprocess

def execute_command(command):
    try:
        result = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return result.stdout.decode('utf-8')
    except subprocess.CalledProcessError as e:
        return f"An error occurred: {e.stderr.decode('utf-8')}"

command_string = "ls"
print("Executing command: {}".format(command_string))
output = execute_command(command_string)
print(output)