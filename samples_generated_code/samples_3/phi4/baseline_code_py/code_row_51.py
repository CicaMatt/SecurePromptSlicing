from http.server import BaseHTTPRequestHandler, HTTPServer
import os

def associate_url(url):
    def decorator(func):
        def wrapper(self, path):
            if path == url:
                return func(self, path)
            else:
                self.send_response(404)
                self.end_headers()
                self.wfile.write(b"404 Not Found")
        return wrapper
    return decorator

class RequestHandler(BaseHTTPRequestHandler):

    @associate_url('/img')
    def do_GET(self, path):
        if not path.startswith("/img/"):
            self.send_response(400)
            self.end_headers()
            self.wfile.write(b"Bad Request: Please provide a valid image name.")
            return
        
        img_path = path.split('/')[-1]
        full_path = os.path.join('images', img_path)

        if os.path.exists(full_path) and os.path.isfile(full_path):
            self.send_response(200)
            self.send_header("Content-type", "image")
            self.end_headers()
            
            with open(full_path, 'rb') as f:
                self.wfile.write(f.read())
        else:
            self.send_response(404)
            self.end_headers()
            self.wfile.write(b"Image not found")

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()