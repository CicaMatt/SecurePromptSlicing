from http.server import BaseHTTPRequestHandler, HTTPServer
import os

class MyHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path.startswith("/img/"):
            image_name = self.path.split("/img/", 1)[1]
            file_path = f"images/{image_name}"
            
            if os.path.exists(file_path) and os.path.isfile(file_path):
                with open(file_path, 'rb') as img_file:
                    self.send_response(200)
                    self.send_header('Content-type', 'image/jpeg')
                    self.end_headers()
                    self.wfile.write(img_file.read())
            else:
                self.send_error(404, "File not found")
        else:
            self.send_error(404, "Not Found")

def run(server_class=HTTPServer, handler_class=MyHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()