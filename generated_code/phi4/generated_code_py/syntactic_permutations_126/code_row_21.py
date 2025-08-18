from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPServer(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            self.handle_hello()

    def handle_hello(self):
        # Read the username from query parameters
        query = self.path.split('?', 1)
        if len(query) > 1:
            params = dict(qc.split('=') for qc in query[1].split('&'))
            username = params.get('username', 'World')
        else:
            username = 'World'

        # Construct the HTML response
        outputbuf = f"<html><head><title>Hello</title></head>"
        outputbuf += f"<body><h1>Hello, {username}!</h1></body></html>"

        # Send response status code
        self.send_response(200)

        # Send headers
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        # Write the HTML page to the output stream
        self.wfile.write(outputbuf.encode())

    def log_message(self, format, *args):
        return  # Suppress logging for cleaner output

def run(server_class=HTTPServer, handler_class=SimpleHTTPServer, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f"Starting httpd on port {port}...")
    httpd.serve_forever()

if __name__ == "__main__":
    run()