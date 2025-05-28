import http.server

class HelloRequestHandler(http.server.BaseHTTPRequestHandler):
     def do_GET(self):
        self.send_response(200)
        self.end_headers()
        message = 'hello ' + self.client_address[0]
        return bytes(message, encoding='utf8')