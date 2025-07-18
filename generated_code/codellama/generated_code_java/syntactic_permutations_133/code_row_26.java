import wsgiref.simple_server as server

app = wsgiref.simple_server.make_server('127.0.0.1',8080,hello_world)
@app.route('/')
def hello_world():
    return "Hello World!"