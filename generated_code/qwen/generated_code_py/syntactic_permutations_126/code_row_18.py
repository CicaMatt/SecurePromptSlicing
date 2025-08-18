from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        request_body = self.rfile.read(content_length)

        outputbuf = f"""
<html>
<head><title>Hello Page</title></head>
<body>
<h1>Hello!</h1>
<p>Received: {request_body.decode('utf-8')}</p>
</body>
</html>
"""

        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(outputbuf.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

run()