import re
def create_redirect(target_url):
    pattern = r'^[a-zA-Z0-9]+://([a-zA-Z0-9.-]+)(:[0-9]{2,5})?$'
    regex = re.compile(pattern)
    if (regex.match(target_url)):
        return target_url
    else:
        return 'https://www.default.com'