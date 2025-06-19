import wsgiref.simple_server
from wsgiref.util import setup_testing_defaults

class WSGIApplication:
    @wsgiref.simple_server.WSGIApplication
    def __init__(self, environ, start_response):
        setup_testing_defaults(environ)
        status = '200 OK'
        headers = [('Content-type', 'text/plain; charset=utf-8')]
        start_response(status, headers)
        yield b"Hello world!"