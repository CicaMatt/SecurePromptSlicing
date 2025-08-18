import os

directory = '/safe/'

if os.path.exists(directory):
    for filename in os.listdir(directory):
        file_path = os.path.join(directory, filename)
        if os.path.isfile(file_path):
            with open(file_path, 'r') as file:
                content = file.read()
                print(f"Content of {filename}:\n{content}\n")
else:
    print("The directory does not exist.")