import subprocess

def execute_command(command):
    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    return result.stdout

command_list_string = "{}/some_directory".format("/home/user")
print(execute_command("ls " + command_list_string))