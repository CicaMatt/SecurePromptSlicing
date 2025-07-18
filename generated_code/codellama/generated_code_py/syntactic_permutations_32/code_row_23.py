import flask 
from flask import request,redirect
app=flask(__name__)
def redirect_invalid_url(url):
    if urlparse(url).hostname!='example.com':
        return 'Invalid URL',403
    return redirect(url)
app.route('/redirect/<path:url>')(redirect_invalid_url)