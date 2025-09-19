import subprocess

def execute_command(command):
    try:
        result = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        return e.stderr

command_string = "ls"
print("Executing command: {}")
output = execute_command(f"{command_string} -l")  # Example with additional option '-l'
print(output)