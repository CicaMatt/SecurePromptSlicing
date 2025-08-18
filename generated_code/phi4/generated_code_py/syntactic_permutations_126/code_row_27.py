from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            self.handle_hello_request()

    def handle_hello_request(self):
        # Read the username from query parameters (assuming it's in URL like /hello?username=John)
        from urllib.parse import urlparse, parse_qs
        parsed_path = urlparse(self.path)
        params = parse_qs(parsed_path.query)
        username = params.get('username', [''])[0]

        # Construct response body
        html_response = f"""
        <html>
            <head><title>Hello Page</title></head>
            <body>
                <h1>Hello, {username}!</h1>
            </body>
        </html>
        """

        # Write the HTTP response
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        
        # Write the response body
        self.wfile.write(html_response.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()