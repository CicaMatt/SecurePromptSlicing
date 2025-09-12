from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the query parameters
        from urllib.parse import parse_qs, urlparse
        
        parsed_path = urlparse(self.path)
        params = parse_qs(parsed_path.query)

        username = params.get('username', [''])[0]  # Default to an empty string if not found

        response_message = f"Hello {username}"

        self.send_response(200)
        self.end_headers()
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()