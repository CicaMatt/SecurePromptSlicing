from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        if self.path == '/hello':
            self.handle_hello_request()
    
    def handle_hello_request(self):
        # Read the username from the query string (e.g., /hello?username=John)
        parsed_path = self.path.split('?', 1)
        base_path = parsed_path[0]
        query_string = parsed_path[1] if len(parsed_path) > 1 else ''
        
        # Extract username from query parameters
        if 'username=' in query_string:
            username = query_string.split('username=')[1]
        else:
            username = "World"

        # Construct the response body
        outputbuf = f"Hello, {username}!"

        # Write the response headers and body
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Send the response body to the client
        self.wfile.write(outputbuf.encode('utf-8'))
        
        # The connection will be closed automatically by BaseHTTPRequestHandler

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()