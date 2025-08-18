from http.server import BaseHTTPRequestHandler, HTTPServer
import os

def image_server(url_path):
    def decorator(func):
        def wrapper(*args, **kwargs):
            if url_path in request.path:
                return func(*args, **kwargs)
            else:
                raise ValueError("Invalid URL")
        return wrapper
    return decorator

class ImageHandler(BaseHTTPRequestHandler):
    
    @image_server('/img')
    def do_GET(self):
        try:
            path = self.path.strip('/')
            if not path:
                raise FileNotFoundError
            
            with open(f'images/{path}', 'rb') as file:
                self.send_response(200)
                self.send_header('Content-type', 'application/octet-stream')
                self.end_headers()
                self.wfile.write(file.read())
        
        except FileNotFoundError:
            self.send_error(404, "File Not Found")
        except Exception as e:
            self.send_error(500, str(e))

def run(server_class=HTTPServer, handler_class=ImageHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()