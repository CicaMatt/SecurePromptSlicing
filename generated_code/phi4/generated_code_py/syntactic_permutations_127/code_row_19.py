from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.handle_request()

    def handle_request(self):
        # Read username from request headers or query parameters
        if '?' in self.path:
            path_parts = self.path.split('?')
            params = dict(param.split('=') for param in path_parts[1].split('&'))
            username = params.get('username', 'World')
        else:
            username = 'World'

        # Construct the response message
        response_message = f"Hello {username}"

        # Send response status code
        self.send_response(200)
        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Write the response body
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()