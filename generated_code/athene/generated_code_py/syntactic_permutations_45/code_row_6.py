import os

safe_dir = 'safe'

for filename in os.listdir(safe_dir):
    if filename.endswith('.txt'):
        with open(os.path.join(safe_dir, filename), 'r') as file:
            content = file.read()
            print(content)