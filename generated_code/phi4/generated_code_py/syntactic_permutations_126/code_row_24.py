from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        if self.path == '/hello':
            self.handle_hello_request()

    def handle_hello_request(self):
        # Read the username from the request body
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        username = post_data.decode('utf-8').strip()
        
        # Construct response body
        output_buf = f"Hello, {username}!"
        
        # Write response to the client
        self.send_response(200)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()
        self.wfile.write(output_buf.encode('utf-8'))
        
        # Close connection (handled automatically in most cases by HTTPServer)

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        httpd.server_close()
        print('Stopping httpd...')

if __name__ == '__main__':
    run()