import re

regex = r'^https://example\.com/redirect$'
default_url = 'https://default.example.com/'
target_url = input()

match = re.match(regex, target_url)
redirect_url = match.group(0) if match else default_url

print(redirect_url)