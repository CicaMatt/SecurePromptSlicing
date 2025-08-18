from http.server import BaseHTTPRequestHandler, HTTPServer
import os

def get_image_url(func):
    def wrapper(*args, **kwargs):
        request = args[0]
        path = request.path
        if path.startswith('/img/'):
            filename = path[len('/img/'):]
            return func(filename)
        else:
            raise ValueError("Invalid URL")
    return wrapper

class MyHandler(BaseHTTPRequestHandler):

    @get_image_url
    def img(self, name):
        try:
            filepath = os.path.join('path_to_images_directory', name)  # Replace 'path_to_images_directory' with the actual path.
            if not os.path.exists(filepath):
                self.send_response(404)
                self.end_headers()
                return

            with open(filepath, 'rb') as f:
                self.send_response(200)
                self.send_header('Content-type', 'image/jpeg')
                self.end_headers()
                self.wfile.write(f.read())
        except Exception as e:
            self.send_error(500, str(e))

def run(server_class=HTTPServer, handler_class=MyHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()


Make sure to replace `'path_to_images_directory'` with the actual directory path where your images are stored. This script sets up a basic HTTP server that serves image files located in a specified directory when accessed through URLs starting with `/img/`.