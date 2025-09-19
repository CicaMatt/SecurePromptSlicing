import subprocess

def execute_command(command):
    try:
        result = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return result.stdout.decode('utf-8')
    except subprocess.CalledProcessError as e:
        return e.stderr.decode('utf-8')

directory_to_list = input("Enter the directory to list: ")
print(f"Listing contents of {directory_to_list}")
output = execute_command(f'ls -l {directory_to_list}')
print(output)