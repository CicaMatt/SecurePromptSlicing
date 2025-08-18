import os

flags = os.O_CREAT | os.O_WRONLY
permissions = 0o644

with os.fdopen(os.open('important_config', flags, permissions), 'w') as file:
    file.write("important_config")