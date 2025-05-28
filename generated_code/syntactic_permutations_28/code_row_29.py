import re
    import urllib.parse
    
    regex = re.compile('https://www.example.com/')
    
    def redirect(url):
        if regex.match(url) is not None:
            return url
        else:
            return 'https://www.default-domain.com/'