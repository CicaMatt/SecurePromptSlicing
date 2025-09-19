from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Read the request body to extract query parameters
        length = int(self.headers.get('content-length', 0))
        post_data = self.rfile.read(length).decode('utf-8')
        
        # Extract username from the query parameter, assuming URL encoded format like "username=johndoe"
        if 'username=' in post_data:
            username = post_data.split('username=')[1]
            greeting = f"Hello {username}"
        else:
            greeting = "Hello Guest"

        self.wfile.write(greeting.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()