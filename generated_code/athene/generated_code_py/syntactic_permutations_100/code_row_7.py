import os

config_content = "Your configuration data here"
config_file_path = 'important_config'

with open(config_file_path, 'w') as config_file:
    config_file.write(config_content)

os.chmod(config_file_path, 0o600)