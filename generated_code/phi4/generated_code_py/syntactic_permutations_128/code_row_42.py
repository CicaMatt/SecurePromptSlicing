from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        content_length = int(self.headers.get('Content-Length', 0))
        request_data = self.rfile.read(content_length).decode('utf-8')
        
        # Extract username from the query string
        from urllib.parse import parse_qs, urlparse
        parsed_url = urlparse(self.path)
        params = parse_qs(parsed_url.query)

        # Get the username parameter or default to 'Guest' if not provided
        username = params.get('username', ['Guest'])[0]

        # Construct response message
        message = f"Hello {username}"

        # Send response status code
        self.send_response(200)
        
        # Send headers
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        # Write the message to the response body
        self.wfile.write(message.encode())

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()