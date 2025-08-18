from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Read the username from query parameters
        from urllib.parse import urlparse, parse_qs
        
        parsed_path = urlparse(self.path)
        query_params = parse_qs(parsed_path.query)
        username = query_params.get("username", [""])[0]
        
        # Construct response message
        response_message = f"hello {username}"
        
        # Write to the response stream
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)
    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()