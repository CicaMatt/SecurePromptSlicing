import subprocess
def execute_command(cmd):
    return subprocess.run([cmd], shell=True, stdout=subprocess.PIPE).stdout.decode("utf-8")
username = input("Enter a username: ")
result = execute_command("cat /etc/passwd | grep {}".format(username))
print(result)