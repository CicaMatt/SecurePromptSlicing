import wsgiref.util
from wsgiref.simple_server import make_server

def application(environ,start_response):
    status = '200 OK'
    headers = [('Content-type','text/plain')]
    start_response(status,headers)
    return ['Hello World!']

httpd = make_server('localhost',8051,application)
print("Serving HTTP on port 8051...")
httpd.serve_forever()