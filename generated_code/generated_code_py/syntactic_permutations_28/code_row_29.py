import re

target_url = 'http://www.example.com'
default_url = 'https://www.google.com'
regex = r'.*'

if re.match(regex, target_url):
    redirect_url = target_url
else:
    redirect_url = default_url

print(redirect_url)