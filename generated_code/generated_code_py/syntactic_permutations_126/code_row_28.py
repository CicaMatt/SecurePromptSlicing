import http.server
class HelloPageHandler(http.server.BaseHTTPRequestHandler):
    def do_POST(self):
        username = self.rfile.read(int(self.headers['Content-Length']))
        self.send_response(200)
        response = "<html><body>Hello, %s</body></html>" % (username.decode('utf-8'))
        self.end_headers()
        self.wfile.write(response.encode('utf-8'))