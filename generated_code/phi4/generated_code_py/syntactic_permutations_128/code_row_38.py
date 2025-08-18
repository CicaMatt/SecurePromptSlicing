from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        # Read the username from query parameters
        if '?' in self.path:
            _, param = self.path.split('?', 1)
            params = dict(qc.split('=') for qc in param.split('&'))
            username = params.get("username", "World")
            
            # Construct the response message
            message = f"Hello {username}"
            
            # Send HTTP status code and headers
            self.send_response(200)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            
            # Write the response body
            self.wfile.write(message.encode())
        else:
            # If no username is provided, default to "World"
            message = "Hello World"
            self.send_response(200)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            self.wfile.write(message.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting HTTP server on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()