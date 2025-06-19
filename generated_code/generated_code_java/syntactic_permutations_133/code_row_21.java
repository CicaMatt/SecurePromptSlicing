import wsgiref.simple_server as server
from wsgiref.util import setup_testing_defaults

app = server.make_server('', 8000)

@app.request_handler
def hello_world(environ, start_response):
    status = '200 OK'
    headers = [('Content-type', 'text/plain')]
    response_body = 'Hello World!'
    
    return status, headers, response_body

app.serve_forever()