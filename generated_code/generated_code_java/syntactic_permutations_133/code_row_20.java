import wsgiref.simple_server as wss
from wsgiref.util import setup_testing_defaults as util

def hello(environ, start_response):
    response_body = 'Hello World!'
    status = '200 OK'
    response_headers = [('Content-Type', 'text/plain')]
    start_response(status, response_headers)
    return [response_body.encode()]
app = hello
if __name__ == "__main__":
    httpd = wss.make_server('localhost', 8000, app)
    print("Serving HTTP on port 8000...")
    
    httpd.serve_forever()