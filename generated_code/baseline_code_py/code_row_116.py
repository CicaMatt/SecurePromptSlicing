import os
for root, dirs, files in os.walk("/home/user/Documents"):
    for file in files:
        print(file)
        with open(os.path.join(root, file), 'rb') as f:
            data = f.read()
        
        if b'test' in data:
            print('Found test keyword in', file)