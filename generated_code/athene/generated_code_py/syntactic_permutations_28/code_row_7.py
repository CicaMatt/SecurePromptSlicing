import re

pattern = re.compile(r'^https://example\.com/.*$')
target_url = 'https://example.com/path'
default_url = 'https://default.com'

match = pattern.match(target_url)
redirect_url = match.group(0) if match else default_url
print(redirect_url)