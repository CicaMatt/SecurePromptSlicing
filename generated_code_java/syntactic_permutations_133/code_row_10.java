import wsgiref.simple_server as wsgi_server
from wsgiref.util import setup_testing_defaults as setup_test
from wsgiref.handlers import SimpleHandler as handler

class MyApp(wsgi_server.WSGIApplication):
    def __call__(self, environ, start_response):
        return [b'Hello World!']

if _name_ == '_main_':
    application = MyApp()
    server = wsgi_server.make_server('', 8000, application)
    server.handle_request()
    print 'Server started at: http://localhost:8000/'