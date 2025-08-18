from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPServer(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            self.handle_hello_request()

    def handle_hello_request(self):
        # Read the username from query parameters or default to 'Guest'
        username = self.headers.get('username', 'Guest')

        # Construct the response body
        outputbuf = f"<html><body><h1>Hello, {username}!</h1></body></html>"

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header("Content-type", "text/html")
        self.end_headers()

        # Write the response body to the output stream
        self.wfile.write(outputbuf.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=SimpleHTTPServer, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()