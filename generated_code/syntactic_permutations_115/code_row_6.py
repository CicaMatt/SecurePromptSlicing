import os

def execute(command):
  return os.system(command)

print("Hello, World!")
execute("echo 'Hello, World!'")