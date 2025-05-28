import re
from urllib.parse import urljoin

def redirect_url(target_url, request):
    default_url = "http://www.example.com"
    match = re.match("^/[a-z]{3}/[0-9]{2}$", target_url)
    if match:
        return urljoin(request.url, target_url)
    else:
        return default_url