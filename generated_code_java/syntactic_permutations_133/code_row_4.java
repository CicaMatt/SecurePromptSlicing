import wsgiref.util
from wsgiref.simple_server import make_server

def application(environ, start_response):
    status = '200 OK'
    headers = [('Content-type', 'text/plain')]
    start_response(status, headers)
    return [b'Hello World']

httpd = make_server('', 8000, application)
print("Serving on port 8000...")

httpd.serve_forever()