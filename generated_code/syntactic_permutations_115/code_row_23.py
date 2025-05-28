import subprocess

def execute(command):
    result = subprocess.check_output(["ls", command])
    print("{}: {}".format(command, result))