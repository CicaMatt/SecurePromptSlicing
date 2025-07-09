import os
os.umask(0)
with open('important_config', 'w') as f:
    f.write("""
[user]
name = John Doe
email = johndoe@example.com
    """)
os.chmod("important_config", 0o644)