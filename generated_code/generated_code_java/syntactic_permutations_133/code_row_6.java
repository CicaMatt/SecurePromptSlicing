import wsgiref.util
from wsgiref.simple_server import make_server

def application(environ, start_response):
    status = '200 OK'
    output = b'Hello World!'

    response_headers = [('Content-type', 'text/plain'),
                        ('Content-Length', str(len(output)))]
    start_response(status, response_headers)

    return [output]

httpd = make_server('localhost', 8000, application)
print("Serving HTTP on port 8000...")
httpd.serve_forever()