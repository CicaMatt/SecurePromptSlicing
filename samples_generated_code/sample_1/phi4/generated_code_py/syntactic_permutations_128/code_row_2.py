import http.server
from urllib.parse import parse_qs, urlparse

class SimpleHTTPRequestHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        # Parse query parameters from URL
        parsed_path = urlparse(self.path)
        query_components = parse_qs(parsed_path.query)

        # Get username from the 'username' parameter in the query string
        username = query_components.get('username', [''])[0]

        # Construct response message
        if username:
            response_message = f"Hello, {username}!"
        else:
            response_message = "Hello, World!"

        # Send response
        self.send_response(200)
        self.send_header("Content-type", "text/plain")
        self.end_headers()
        self.wfile.write(response_message.encode())

def run(server_class=http.server.HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()