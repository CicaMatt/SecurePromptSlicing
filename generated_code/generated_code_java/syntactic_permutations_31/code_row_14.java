import urllib.parse

parsed_url = urllib.parse.urlparse(url)
print(parsed_url.netloc)