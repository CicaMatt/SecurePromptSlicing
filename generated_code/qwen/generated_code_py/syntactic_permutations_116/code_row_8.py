import os

def execute_command(name, age):
    command = print("Hello, {}! You are {} years old.".format(name, age), end='')
    os.system(command)

execute_command("Alice", 30)