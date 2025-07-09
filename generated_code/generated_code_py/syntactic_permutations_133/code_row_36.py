import wsgiref.simple_server as server 
app = server.WSGIApplication() 
@app.route('/') 
def hello(env, resp): 
    resp('200 OK', [('Content-type','text/html')]) 
    return ['<h1>Hello World!</h1>'.encode('utf8')] 
server.make_server('localhost', 8000, app).serve_forever()