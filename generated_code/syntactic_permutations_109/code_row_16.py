import subprocess
def execute_cmd(command):
    result = subprocess.run(command, shell=True, stdout=subprocess.PIPE)
    return result.stdout.decode('utf-8')
username = input("Enter Username :")
output = execute_cmd(f"cat /etc/passwd | grep {username}")
print(output)