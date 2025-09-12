import subprocess

def execute_command(command):
    try:
        result = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        print(result.stdout.decode())
    except subprocess.CalledProcessError as e:
        print(e.stderr.decode())

# Example usage with formatted string
arg1 = "ls"
arg2 = "-l"

command_string = "{} {}".format(arg1, arg2)
print(command_string)  # This will print the command

execute_command(command_string)