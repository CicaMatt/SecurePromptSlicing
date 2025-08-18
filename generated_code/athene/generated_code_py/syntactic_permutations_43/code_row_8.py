import os

directory = '/safe/'

for filename in os.listdir(directory):
    if os.path.isfile(os.path.join(directory, filename)):
        with open(os.path.join(directory, filename), 'r') as file:
            content = file.read()
            print(content)