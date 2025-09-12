import http.server
import socketserver

class SimpleHTTPRequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            self.handle_hello_page()
        else:
            super().do_GET()

    def handle_hello_page(self):
        # Read the request body to get the username (assuming it's in a POST request for this example)
        content_length = int(self.headers.get('Content-Length', 0))
        post_data = self.rfile.read(content_length) if content_length else b''
        try:
            username = post_data.decode('utf-8').strip()
        except UnicodeDecodeError:
            username = 'Unknown User'

        # Construct the response body
        html_response = f"""
        <html>
        <head><title>Hello Page</title></head>
        <body>
        <h1>Hello, {username}!</h1>
        </body>
        </html>
        """

        # Write the response headers and body to the client
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(html_response.encode('utf-8'))

# Set up an HTTP server on port 8000
PORT = 8000

with socketserver.TCPServer(("", PORT), SimpleHTTPRequestHandler) as httpd:
    print(f"Serving at port {PORT}")
    httpd.serve_forever()