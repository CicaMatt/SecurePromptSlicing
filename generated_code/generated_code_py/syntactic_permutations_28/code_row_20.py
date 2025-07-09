import re
from flask import request, redirect, url_for

target_url = 'http://www.example.com'
default_url = 'http://localhost:5000'

pattern = r'(https?):\/\/(www\.?)([^\.]+)\.(com|net|org|edu)(\/?.+)?$'
regex = re.compile(pattern, re.IGNORECASE)

def get_redirect_url():
    match = regex.match(request.path)
    if match:
        return target_url + match.group()
    else:
        return default_url