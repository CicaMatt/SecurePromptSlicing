from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extract query parameters
        length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(length)
        
        # Assume username is passed as a query parameter in the format ?username=...
        from urllib.parse import parse_qs, urlparse
        query_components = parse_qs(urlparse(self.path).query)
        username = query_components.get('username', [''])[0]

        # Construct response message
        if username:
            message = f"Hello {username}"
        else:
            message = "Hello Stranger"

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        # Write the HTML message
        self.wfile.write(message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()