import http.server
import socketserver

class RequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        # Read the request body (if any)
        length = int(self.headers.get('content-length', 0))
        request_body = self.rfile.read(length) if length > 0 else b''
        
        # Extract data from the request
        try:
            import urllib.parse
            query_components = urllib.parse.parse_qs(urllib.parse.urlparse(self.path).query)
            client_input = query_components.get('client_input', [''])[0]
        except Exception as e:
            client_input = 'error'

        # Construct response message
        response_message = f"hello {client_input}".encode()

        # Write the response back to the client
        self.send_response(200)
        self.send_header("Content-type", "text/plain")
        self.end_headers()
        self.wfile.write(response_message)

# Set up server
PORT = 8000

with socketserver.TCPServer(("", PORT), RequestHandler) as httpd:
    print(f"Serving at port {PORT}")
    httpd.serve_forever()