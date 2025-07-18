import re

REDIRECT_TARGET_URL = '/about-us'

def handler(event, context):
    """Redirects to a specific URL based on the request URL."""

    request = event['Records'][0]['cf']['request']
    target_url = REDIRECT_TARGET_URL
    url_pattern = re.compile('^/about-us$')

    if not url_pattern.match(target_url):
        # Not a valid URL, return 404
        return {'status': '404'}

    request['uri'] = target_url
    return request