from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        # Read username from query parameters (assuming GET method for simplicity)
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        # Construct the response body
        outputbuf = f"<html><body><h1>Welcome, {self.path.lstrip('/')}!</h1></body></html>"

        # Write the response body to the response stream
        self.wfile.write(outputbuf.encode('utf-8'))

    def log_message(self, format, *args):
        return  # Suppress logging for simplicity

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)

    try:
        print(f'Starting httpd on port {port}...')
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        print('Stopping httpd...\n')
        httpd.server_close()

if __name__ == '__main__':
    run()