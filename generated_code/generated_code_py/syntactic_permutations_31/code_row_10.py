import urllib
parsed_url=urlparse(url)
domain=parsed_url.domain
return redirect(url)
abort(404)