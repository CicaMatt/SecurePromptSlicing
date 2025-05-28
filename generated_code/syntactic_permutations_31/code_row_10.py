import urllib
def redirect_url(url):
parsed_url=urlparse(url)
domain=parsed_url.domain
if domain=="example.com":
return redirect(url)
else:
abort(404)