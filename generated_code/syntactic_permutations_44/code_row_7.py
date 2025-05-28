import os

with open('file_name') as f:
    content = f.readlines()

content = [x.strip() for x in content]