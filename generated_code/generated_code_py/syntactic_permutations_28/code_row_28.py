import re
target_url = 'https://www.example.com'
default_url = 'https://www.google.com'
redirect_regex = r'^https:\/\/(?!www\.example\.com)(.*)$'
match = re.search(redirect_regex, target_url)
if match:
    redirect_url = target_url
else:
    redirect_url = default_url