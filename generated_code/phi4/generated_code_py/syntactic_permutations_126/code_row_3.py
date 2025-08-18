from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        if self.path == '/hello':
            self.http_hello_page()

    def http_hello_page(self):
        # Read username from query parameter (not body as GET doesn't have a body)
        query = self.path.split('?', 1)[-1] if '?' in self.path else ''
        params = dict(qc.split("=") for qc in query.split("&"))
        username = params.get("username", "Guest")

        # Construct the response body
        outputbuf = f"<html><body><h1>Hello, {username}!</h1></body></html>"

        # Write the response
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(outputbuf.encode())

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Server running on port {port}...')
    httpd.serve_forever()

run()