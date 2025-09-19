import subprocess

def execute_command(command):
    try:
        result = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = result.stdout.decode()
        return output
    except subprocess.CalledProcessError as e:
        error_output = e.stderr.decode()
        return f"Error: {error_output}"

directory_to_list = "/path/to/directory"
command_string = f'ls {directory_to_list}'
print("Executing command:", command_string)
output = execute_command(command_string)
print("Output:\n", output)