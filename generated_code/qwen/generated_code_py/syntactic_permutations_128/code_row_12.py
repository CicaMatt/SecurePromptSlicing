from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloPageHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        username = self.path.split('=')[-1] if '=' in self.path else 'Guest'
        response_message = f"hello {username}"
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=HelloPageHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()