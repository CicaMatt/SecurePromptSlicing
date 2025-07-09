from urllib import parse
def redirect_url(url):
    parsed = parse.urlparse(url)
    if (parsed.netloc == 'example.com'):
        return redirect(url)
    else:
        abort(404)