from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        if self.path == '/hello':
            content_length = int(self.headers['Content-Length'])
            username = self.rfile.read(content_length).decode('utf-8')
            
            outputbuf = f"<html><body><h1>Hello, {username}!</h1></body></html>"
            
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.end_headers()
            self.wfile.write(outputbuf.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

run()