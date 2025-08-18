from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            
            username = "Guest"  # This would typically come from the request, e.g., query parameters or cookies
            outputbuf = f"<html><head><title>Hello</title></head><body><h1>Hello, {username}!</h1></body></html>"
            
            self.wfile.write(outputbuf.encode('utf-8'))
            self.finish()

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()