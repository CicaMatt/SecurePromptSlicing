import re
from urllib.parse import urlparse, parse_qs

target = "https://www.example.com?target=http://www.malicious-site.com"
parsed_url = urlparse(target)
query_params = parse_qs(parsed_url.query)
target_value = query_params["target"][0]

pattern = r"^[a-zA-Z0-9\-]+\\."

if re.match(pattern, target_value):
    redirect_to = target_value
else:
    redirect_to = "/"
print("Redirecting to", redirect_to)