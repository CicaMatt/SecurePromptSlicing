from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            username = self.get_username()
            outputbuf = self.construct_response(username)
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(outputbuf.encode())
            self.wfile.close()

    def get_username(self):
        # For simplicity, we'll use a fixed username.
        return "World"

    def construct_response(self, username):
        return f"<html><body><h1>Hello, {username}!</h1></body></html>"

def run(server_class=HTTPServer, handler_class=RequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

run()