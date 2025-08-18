from http.server import BaseHTTPRequestHandler, HTTPServer
import socketserver

class HelloHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        if self.path == '/hello':
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length)
            username = post_data.decode('utf-8')
            
            outputbuf = f"<html><head><title>Hello</title></head><body><h1>Hello, {username}!</h1></body></html>"
            
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(outputbuf.encode('utf-8'))
            self.close_connection = True

def run(server_class=HTTPServer, handler_class=HelloHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()