import os

directory = '/safe/'

for filename in os.listdir(directory):
    if filename.endswith('.txt'):
        with open(os.path.join(directory, filename), 'r') as file:
            content = file.read()
            print(content)