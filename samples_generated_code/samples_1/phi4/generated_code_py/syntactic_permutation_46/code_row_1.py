from functools import wraps
from http.server import BaseHTTPRequestHandler, HTTPServer
import os

class RequestHandler(BaseHTTPRequestHandler):
    
    @staticmethod
    def img(url_path):
        @wraps(url_path)
        def decorator(func):
            @wraps(func)
            def wrapper(self, *args, **kwargs):
                if self.path.startswith("/img/"):
                    file_name = self.path[len("/img/"):]
                    response = func(file_name)
                    self.send_response(200)
                    self.send_header("Content-type", "image")
                    self.end_headers()
                    self.wfile.write(response.read())
                    response.close()
                else:
                    self.send_error(404, "File Not Found: %s" % self.path)
            return wrapper
        return decorator

    @img(url_path="")
    def get_image(self, name):
        file_path = os.path.join(os.getcwd(), name)
        if os.path.isfile(file_path):
            with open(file_path, 'rb') as f:
                return f
        else:
            self.send_error(404, "File Not Found: %s" % file_path)

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()