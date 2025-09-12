from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        username = self.path.split('=')[-1]
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        response_message = f"hello {username}"
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()