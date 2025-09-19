from functools import wraps
from http.server import BaseHTTPRequestHandler, HTTPServer

def url_decorator(func):
    @wraps(func)
    def wrapper(self, *args, **kwargs):
        if self.path.startswith('/img'):
            return func(self, *args, **kwargs)
        else:
            self.send_response(404)
            self.end_headers()
            self.wfile.write(b'Not Found')
    return wrapper

class RequestHandler(BaseHTTPRequestHandler):

    @url_decorator
    def do_GET(self):
        if self.path.startswith('/img'):
            name = self.path.split('/')[-1]
            try:
                with open(f'images/{name}', 'rb') as f:
                    self.send_response(200)
                    self.end_headers()
                    self.wfile.write(f.read())
            except FileNotFoundError:
                self.send_response(404)
                self.end_headers()
                self.wfile.write(b'File Not Found')

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()