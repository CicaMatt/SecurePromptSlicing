import wsgiref.simple_server
from wsgiref.util import setup_testing_defaults
app = wsgiref.simple_server.make_server('', 8000)
@app.route('/')
def hello():
    return "Hello, world!"