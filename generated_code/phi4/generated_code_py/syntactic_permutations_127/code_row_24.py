from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Read the username from query parameters
        parsed_path = self.path.split('?')
        if len(parsed_path) > 1:
            query_params = dict(param.split('=') for param in parsed_path[1].split('&'))
            username = query_params.get('username', 'World')
        else:
            username = 'World'
        
        # Construct response
        response_content = f"Hello {username}"
        
        # Write the response to the output stream
        self.wfile.write(response_content.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()