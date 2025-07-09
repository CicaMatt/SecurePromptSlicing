import urlparse
def redirect_url(url):
    parsed_url = urlparse.urlparse(url)
    if parsed_url.netloc == 'example.com':
        return redirect(url)
    else:
        abort(404)