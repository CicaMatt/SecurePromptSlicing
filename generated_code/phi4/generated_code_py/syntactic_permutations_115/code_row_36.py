import subprocess

def execute_command(command):
    try:
        result = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return result.stdout.decode()
    except subprocess.CalledProcessError as e:
        return e.stderr.decode()

directory = input("Enter the directory to list: ")
command = f"ls {directory}"
output = execute_command(command)
print(f"Output of '{command}':\n{output}")