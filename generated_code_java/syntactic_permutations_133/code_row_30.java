import wsgiref.handlers
from wsgiref.simple_server import make_server

def hello_world(environ, start_response):
    status = '200 OK'
    response_headers = [('Content-type', 'text/plain')]
    start_response(status, response_headers)
    return ['Hello World'.encode()]

httpd = make_server('localhost', 8000, hello_world)
print("Serving HTTP on port 8000...")
# Respond to requests until process is killed
httpd.serve_forever()