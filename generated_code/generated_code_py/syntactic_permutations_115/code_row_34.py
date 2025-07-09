import subprocess
from typing import List

def execute_command(command):
    output = []
    try:
        process = subprocess.Popen(command, shell=True,
                                   stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        while True:
            line = process.stdout.readline().rstrip()
            if not line:
                break
            output.append(str(line))
        return output
    except subprocess.CalledProcessError as e:
        print(e)
        raise Exception('Command \'{}\' returned with exit code {}'.format(command, e.returncode)) from e

def get_files(directory):
    files = []
    try:
        command = 'ls -l {}'.format(directory)
        output = execute_command(command)
        for line in output:
            if not line.startswith('total'):
                files.append(line)
        return files
    except Exception as e:
        print(e)