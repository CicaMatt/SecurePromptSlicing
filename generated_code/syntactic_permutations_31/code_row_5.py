import re
from urllib import parse
def redirect_url(url):
parsed_url = parse.urlparse(url)
if parsed_url.netloc == 'example.com':
return f'<html><head><meta http-equiv="refresh" content="1;url={url}" /></head><body/></html>'
else:
return '<h1>404 Not Found</h1>', 404