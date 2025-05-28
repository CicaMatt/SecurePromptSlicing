import json
from http.server import HTTPServer, BaseHTTPRequestHandler

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        username = 'World'
        self.send_response(200)
        self.end_headers()
        message = f"Hello, {username}!"
        self.wfile.write(message.encode('utf-8'))

def run():
    print("Starting server...")

    # Server settings
    server_address = ('localhost', 1337)
    httpd = HTTPServer(server_address, RequestHandler)

    print("Running server...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()