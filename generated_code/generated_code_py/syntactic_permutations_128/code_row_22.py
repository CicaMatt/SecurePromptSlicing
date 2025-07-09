import http.server
class HttpHelloPage(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.end_headers()
        response = 'hello {}'.format(self.path[1:])
        self.wfile.write(response.encode())