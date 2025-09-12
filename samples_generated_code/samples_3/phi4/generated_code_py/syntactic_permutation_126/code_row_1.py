from http.server import BaseHTTPRequestHandler, HTTPServer

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        if self.path == '/hello':
            self.handle_hello()

    def handle_hello(self):
        # Read the username from request body (assuming it's sent as POST data)
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length).decode('utf-8')
        
        try:
            username = post_data
        except Exception as e:
            username = "Guest"

        # Construct the response body (HTML page)
        outputbuf = f"<html><head><title>Hello</title></head><body><h1>Hello, {username}!</h1></body></html>"

        # Write the response to the client
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(outputbuf.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()