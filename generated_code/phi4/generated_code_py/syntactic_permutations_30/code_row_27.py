import re
from urllib.parse import urlparse, parse_qs

def redirect_user(url):
    parsed_url = urlparse(url)
    query_params = parse_qs(parsed_url.query)
    
    if 'target' in query_params:
        target_variable = query_params['target'][0]
        
        # Regular expression to match the pattern: one or more alphanumeric characters or hyphens followed by a period
        pattern = r'^[a-zA-Z0-9\-]+\.$'
        
        if re.match(pattern, target_variable):
            return f"Redirecting to: {target_variable}"
        else:
            return "Redirecting to root of the site"
    else:
        return "No target parameter found. Redirecting to root of the site"

# Example usage
url = "http://example.com/page?target=abc-.com&other_param=value"
print(redirect_user(url))