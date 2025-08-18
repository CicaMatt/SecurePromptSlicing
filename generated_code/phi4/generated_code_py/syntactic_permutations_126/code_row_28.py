from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            self.handle_hello()
    
    def handle_hello(self):
        # Read username from query parameter or set a default value
        from urllib.parse import parse_qs, urlparse
        
        parsed_path = urlparse(self.path)
        query_params = parse_qs(parsed_path.query)
        
        username = query_params.get('username', ['Guest'])[0]
        
        # Construct the response body (HTML page)
        response_body = f"<html><body><h1>Hello, {username}!</h1></body></html>"
        
        # Write the response headers
        self.send_response(200)  # HTTP status code for "OK"
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Write the response body
        self.wfile.write(response_body.encode('utf-8'))
    
def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting HTTP server on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()