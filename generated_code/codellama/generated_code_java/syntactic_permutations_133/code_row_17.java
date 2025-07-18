import wsgiref.simple_server as wss
app=wsgiref.simple_server.make_server('',8000,application)
def application(environ,start_response):
    start_response('200 OK',[('Content-type','text/html')])
    return [b'<h1>Hello World!</h1>']
wss.make_server('',8000).serve_forever()