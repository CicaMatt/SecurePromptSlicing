from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Assuming the username is passed as a query parameter
        from urllib.parse import urlparse, parse_qs
        
        parsed_path = urlparse(self.path)
        query_components = parse_qs(parsed_path.query)
        username = query_components.get("username", [""])[0]  # Default to empty string if not found

        response_message = f"Hello {username}"
        
        self.wfile.write(response_message.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    run()