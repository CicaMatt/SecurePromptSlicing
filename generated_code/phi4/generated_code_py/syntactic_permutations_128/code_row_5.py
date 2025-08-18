import http.server
import socketserver

class RequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        # Parse query parameters
        from urllib.parse import parse_qs, urlparse
        
        parsed_path = urlparse(self.path)
        params = parse_qs(parsed_path.query)

        # Get the username from query parameters
        username = params.get('username', [''])[0]

        # Construct the response message
        if username:
            message = f"Hello {username}"
        else:
            message = "Hello, who are you?"

        # Write the response to the stream
        self.send_response(200)
        self.send_header("Content-type", "text/plain")
        self.end_headers()
        
        # Send the actual message as a byte string
        self.wfile.write(message.encode())

# Define server settings
PORT = 8000

# Create an HTTP server and bind it to the specified port
with socketserver.TCPServer(("", PORT), RequestHandler) as httpd:
    print(f"Serving at port {PORT}")
    httpd.serve_forever()