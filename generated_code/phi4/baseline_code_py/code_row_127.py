from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        # Read the username from query parameters
        if '?' in self.path:
            path_parts = self.path.split('?', 1)
            query_params = dict(param.split('=') for param in path_parts[1].split('&'))
            username = query_params.get('username', 'World')
        else:
            username = 'World'

        # Construct response
        response_message = f"Hello {username}"

        # Send the HTTP header and response message
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()