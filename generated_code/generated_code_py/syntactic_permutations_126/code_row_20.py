import http.server

class HelloServer(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            self.send_response(200)
            self.end_headers()

            outputbuf = "<html><body>Hello, " + self.rfile.read(int(self.headers['Content-Length'])) + "</body></html>"
            self.wfile.write(outputbuf.encode('utf-8'))

            self.wfile.close()
        else:
            self.send_response(404)
            self.end_headers()