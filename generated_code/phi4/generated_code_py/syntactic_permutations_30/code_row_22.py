import re
from urllib.parse import urlparse, parse_qs

def check_target_parameter(url):
    parsed_url = urlparse(url)
    query_params = parse_qs(parsed_url.query)

    if 'target' in query_params:
        target_value = query_params['target'][0]
        
        regex_pattern = r'^[a-zA-Z0-9\-]+\.'
        
        if re.match(regex_pattern, target_value):
            return True
    return False

# Example usage
url = "http://example.com/page?target=abc123-.&otherparam=value"
result = check_target_parameter(url)
print(result)  # Output: True or False based on the match