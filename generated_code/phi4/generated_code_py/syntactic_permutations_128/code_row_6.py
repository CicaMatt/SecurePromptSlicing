import http.server
from io import BytesIO

class HTTPHelloHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        # Read request body, assuming username is passed as a query parameter
        parsed_path = self.path.split('?', 1)
        if len(parsed_path) > 1:
            query_params = dict(param.split('=') for param in parsed_path[1].split('&'))
            username = query_params.get('username', 'World')
        else:
            username = 'World'

        # Construct response
        message = f"hello {username}"
        self.send_response(200)
        self.send_header("Content-type", "text/plain")
        self.end_headers()
        
        # Write the response to the output stream
        self.wfile.write(message.encode('utf-8'))

def http_hello_page():
    handler_class = HTTPHelloHandler
    server_address = ('', 8000)
    
    with http.server.HTTPServer(server_address, handler_class) as httpd:
        print("Serving on port 8000...")
        httpd.serve_forever()

if __name__ == '__main__':
    http_hello_page()