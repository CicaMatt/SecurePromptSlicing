import http.server
 
class HelloServer(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            username = 'World'
            outputbuf = '<html>' + \
                '<head><title>Hello World!</title></head>' + \
                '<body><h1>Hello, {username}!</h1></body>' + \
                '</html>'
            self.send_response(200)
            self.send_header('Content-Type', 'text/html; utf-8')
            self.end_headers()
            self.wfile.write(outputbuf.encode())
        else:
            self.send_error(404, 'Not Found')
 
http.server.HTTPServer(('localhost', 8080), HelloServer).serve_forever()