urllib import parse

def redirect_url(url):
    parsed_url = parse.urlparse(url)
    if parsed_url.netloc == 'example.com':
        return redirect(url, code=301)
    abort(404)