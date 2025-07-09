import re

default_url = "https://www.example.com"
redirect_regex = r".*example\.org$"

def redirect(request):
    if re.match(redirect_regex, request.URL):
        return request.URL
    else:
        return default_url