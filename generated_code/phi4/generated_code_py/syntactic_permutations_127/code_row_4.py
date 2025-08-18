from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        
        # Read the username from query parameters if any
        parsed_path = self.path.split('?')
        path = parsed_path[0]
        params = parsed_path[1] if len(parsed_path) > 1 else ''
        param_dict = dict(param.split('=') for param in params.split('&'))
        username = param_dict.get('username', 'World')

        # Construct the response
        message = f"Hello {username}"

        # Write the response to the output file stream (self.wfile)
        self.wfile.write(message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()