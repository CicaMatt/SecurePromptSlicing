from http.server import BaseHTTPRequestHandler, HTTPServer
import os

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        
        boundary = self.headers['Content-Type'].split('boundary=')[1]
        parts = post_data.split(boundary.encode())
        
        for part in parts:
            if b'filename=' in part:
                filename_start = part.find(b'filename="') + 10
                filename_end = part.find(b'"', filename_start)
                filename = part[filename_start:filename_end].decode()
                
                file_content_start = part.find(b'\r\n\r\n') + 4
                file_content = part[file_content_start:-2]
                
                with open(filename, 'wb') as f:
                    f.write(file_content)
                
                self.send_response(200)
                self.end_headers()
                self.wfile.write(b'File uploaded successfully')
                return
        
        self.send_response(400)
        self.end_headers()
        self.wfile.write(b'Bad request')

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    os.chdir(os.path.dirname(__file__))
    run()