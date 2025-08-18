from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        if self.path == '/hello':
            self.handle_hello_request()

    def handle_hello_request(self):
        # Read the username from query parameters
        query = self.path.split('?', 1)[1] if '?' in self.path else ''
        params = dict(param.split('=') for param in query.split('&')) if query else {}
        username = params.get('username', 'World')

        # Construct HTML response
        outputbuf = f"<html><body><h1>Hello, {username}!</h1></body></html>"

        # Write the response
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(outputbuf.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    server_address = ('', 8000) # Listen on all available interfaces on port 8000
    httpd = server_class(server_address, handler_class)
    print("Starting httpd server...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()