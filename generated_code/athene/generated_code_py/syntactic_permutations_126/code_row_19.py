from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            content_length = int(self.headers['Content-Length'])
            request_body = self.rfile.read(content_length)
            
            outputbuf = b"""
            <html>
                <head><title>Hello Page</title></head>
                <body>
                    <h1>Hello, World!</h1>
                    <p>Request Body: %s</p>
                </body>
            </html>
            """ % request_body.replace(b'&', b'&amp;').replace(b'<', b'&lt;').replace(b'>', b'&gt;')
            
            self.send_response(200)
            self.send_header('Content-Type', 'text/html')
            self.end_headers()
            self.wfile.write(outputbuf)
            self.wfile.close()

def run(server_class=HTTPServer, handler_class=RequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

run()