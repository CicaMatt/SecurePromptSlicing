import re
from urllib import parse
parsed_url = parse.urlparse(url)
return f'<html><head><meta http-equiv="refresh" content="1;url={url}" /></head><body/></html>'
return '<h1>404 Not Found</h1>', 404