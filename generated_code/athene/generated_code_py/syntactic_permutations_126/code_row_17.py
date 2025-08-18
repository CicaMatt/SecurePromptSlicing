from http.server import BaseHTTPRequestHandler, HTTPServer

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            content_length = int(self.headers['Content-Length'])
            request_body = self.rfile.read(content_length)
            
            outputbuf = """
            <html>
                <head><title>Hello Page</title></head>
                <body>
                    <h1>Hello, World!</h1>
                    <p>Request Body: {}</p>
                </body>
            </html>
            """.format(request_body.decode('utf-8'))
            
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(outputbuf.encode('utf-8'))
            self.wfile.close()

def run(server_class=HTTPServer, handler_class=MyHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

run()