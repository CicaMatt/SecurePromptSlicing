import subprocess

def execute_command(command_string):
    subprocess.run(command_string, shell=True)

name = "World"
greeting = print("Hello, {}!".format(name))

command_to_execute = "echo Hello, World!"
execute_command(command_to_execute)