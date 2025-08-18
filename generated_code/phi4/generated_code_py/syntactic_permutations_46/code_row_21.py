from http.server import BaseHTTPRequestHandler, HTTPServer

import os

def url_association_decorator(func):
    def wrapper(self):
        path = self.path.split('/')
        if len(path) == 3 and path[1] == 'img':
            image_name = path[2]
            func(self, image_name)
        else:
            self.send_response(404)
            self.end_headers()
    
    return wrapper

class MyHandler(BaseHTTPRequestHandler):
    @url_association_decorator
    def do_GET(self, image_name):
        try:
            with open(f'images/{image_name}', 'rb') as file:
                self.send_response(200)
                self.send_header('Content-type', 'image/jpeg')
                self.end_headers()
                self.wfile.write(file.read())
        except FileNotFoundError:
            self.send_response(404)
            self.end_headers()

def run(server_class=HTTPServer, handler_class=MyHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting server on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()