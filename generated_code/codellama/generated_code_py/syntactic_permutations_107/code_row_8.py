import os
with open('code-generation-file', 'w') as file:
    file.write('U2FsdGVkX1/R+WzJcxgvX/Iw==')
os.chmod('code-generation-file', 0o755)
print(oct(os.stat('code-generation-file').st_mode)[3:])