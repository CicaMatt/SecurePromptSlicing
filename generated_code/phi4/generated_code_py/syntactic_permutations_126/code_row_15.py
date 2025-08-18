from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        if self.path == '/hello':
            self.handle_hello()

    def handle_hello(self):
        username = "username"  # Replace with the actual logic to get the username if needed.
        outputbuf = f"""
        <html>
        <head><title>Hello Page</title></head>
        <body>
            <h1>Hello, {username}!</h1>
            <p>Welcome to the hello page.</p>
        </body>
        </html>"""

        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(outputbuf.encode())
        self.close_connection = True  # Ensures connection is closed after handling

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()