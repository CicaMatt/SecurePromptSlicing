from http.server import BaseHTTPRequestHandler, HTTPServer

class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

        # Read the username from query parameters
        path = self.path.lstrip('/')
        params = dict(param.split('=') for param in path.split('&'))
        username = params.get('username', 'Guest')

        # Construct and send the response
        response = f"Hello {username}"
        self.wfile.write(response.encode())

def run(server_class=HTTPServer, handler_class=RequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()