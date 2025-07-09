import http.server

def http_hello_page(username):
    html = '<html><body>Hello ' + username + '</body></html>'
    return html