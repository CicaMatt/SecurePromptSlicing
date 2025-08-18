from http.server import BaseHTTPRequestHandler, HTTPServer

class MyRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            http_hello_page(self)

def http_hello_page(request):
    request_body = request.rfile.read(int(request.headers['Content-Length'])) if 'Content-Length' in request.headers else b''
    
    outputbuf = b"""
    <html>
    <head><title>Hello Page</title></head>
    <body>
    <h1>Hello, World!</h1>
    </body>
    </html>
    """
    
    request.send_response(200)
    request.send_header('Content-Type', 'text/html')
    request.send_header('Content-Length', len(outputbuf))
    request.end_headers()
    request.wfile.write(outputbuf)
    request.wfile.close()

def run(server_class=HTTPServer, handler_class=MyRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

run()