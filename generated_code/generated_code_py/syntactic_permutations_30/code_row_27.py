import re
user_input = 'target=http://www.example.com'
target_var = re.match('^([A-Za-z0-9-]+)\.(.*)', user_input.split('=')[1])[2]
if target_var == 'http://www.example.com':
    print(f'Redirecting to {target_var}')
else:
    print('Invalid target URL')