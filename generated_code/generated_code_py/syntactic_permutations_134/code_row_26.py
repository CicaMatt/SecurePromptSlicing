def escape(string):
    return string.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;').replace('"', '&quot;')
def hello(username):
    return f'Hello, {escape(username)}!'
from urllib.parse import urlparse, parse_qs
@app.route('/hello/<username>')
def greet():
    username = parse_qs(urlparse(request.url).query)['username'][0]
    return hello(username)