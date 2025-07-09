import os

def execute_command(cmd):
    result = os.popen(cmd).read()
    return result

print("{0}".format(execute_command("ls -l")))