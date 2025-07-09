import re
import sys
from urllib.parse import urlsplit, urlunsplit

def main(request):
    """Handle request and return a response."""
    
    # Compile the regular expression once at load time
    regex = re.compile(r'^/(?P<lang>[^/]+)/$')
    
    # Split the URL into its components
    url_parts = urlsplit(request.url)
    
    # Attempt to match the regular expression against the path
    match = regex.match(url_parts.path)
    
    if match:
        # Extract the value of the 'lang' named group from the match
        lang = match.group('lang')
        
        # Return a redirect response with the target URL set to the value of the language
        return RedirectResponse(urlunsplit((url_parts.scheme, url_parts.netloc, f'/{lang}/', url_parts.query, url_parts.fragment)))