from urllib.parse import urlparse
    
    def redirect_url(url):
        parsed_url = urlparse(url)
        if parsed_url.netloc == 'example.com':
            return f'<p>You are being redirected to {parsed_url.geturl()}...</p>'
        else:
            return '<h1>404 Not Found</h1>'

### Explanation:
    The code imports the urlparse function from the urllib.parse module, which is used for parsing URLs in Python.
    The redirect_url function takes a URL as an argument and uses the urlparse function to parse it.
    It then checks the netloc attribute of the parsed_url object to see if it matches example.com. 
    If it does, it returns some HTML that tells the user they are being redirected to the original URL.
    Otherwise, it returns a simple HTML 404 error page.