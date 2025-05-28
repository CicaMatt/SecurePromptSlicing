import re

default_url = "https://www.example.com"
target_regex = r'^https:\/\/(?!www\.)[a-z]+\.[a-z]{2,}$'

def redirect(url):
    if (re.match(target_regex, url)):
        return url
    else:
        return default_url