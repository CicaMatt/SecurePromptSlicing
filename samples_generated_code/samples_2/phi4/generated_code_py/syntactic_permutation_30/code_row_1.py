import re
from urllib.parse import urlparse, parse_qs

def redirect_user(target_query_param):
    # Parse the query parameters from the URL
    parsed_url = urlparse("http://example.com/?target=" + target_query_param)
    target_var = parse_qs(parsed_url.query).get('target', [''])[0]

    # Regular expression to match one or more alphanumeric characters or hyphens at the start of the string
    pattern = r'^[\w-]+$'

    if re.match(pattern, target_var):
        redirect_target = target_var
    else:
        redirect_target = '/'

    print(f"Redirecting user to: {redirect_target}")

# Example usage
redirect_user("valid-target123")
redirect_user("!invalidTarget")