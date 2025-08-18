from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloPageHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Extracting query parameters
        from urllib.parse import urlparse, parse_qs
        parsed_path = urlparse(self.path)
        query_params = parse_qs(parsed_path.query)
        
        # Getting username from query parameters
        username = query_params.get('username', [''])[0]
        
        # Constructing the response
        message = f"Hello {username}".encode()
        
        # Writing the response headers
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Writing the response body
        self.wfile.write(message)

def run(server_class=HTTPServer, handler_class=HelloPageHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()

if __name__ == '__main__':
    run()