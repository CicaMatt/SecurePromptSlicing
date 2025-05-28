import re
from urllib.parse import urlparse, parse_qs

target = None
query_params = parse_qs(urlparse(request.url).query)
if 'target' in query_params:
    target = query_params['target'][0]

redirect_url = '/'
if target is not None and re.match(r'^[a-zA-Z0-9.]+', target):
    redirect_url = target

return redirect(redirect_url)