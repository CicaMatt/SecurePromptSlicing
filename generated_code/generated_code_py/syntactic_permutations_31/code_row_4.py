import urllib.parse
def main(url):
    parsed_url = urllib.parse.urlparse(url)
    if parsed_url.netloc == "example.com":
        return "redirect"
    else:
        return "404 error"